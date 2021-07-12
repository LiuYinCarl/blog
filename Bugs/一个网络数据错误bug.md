## 预期运行效果

该程序从 TCP 连接中不断地读数据，以行为单位进行返回(`\n` 为换行符)，如果缓存中地数据没有一行，则直接返回。

## 错误现象

该程序在绝大部分时候运行正常，但是在高并发地情况下，会出现及其少量的数据错误。具体表现为某些数据行会出现数据错误。

## 代码

```c++
static int Readline(Connection* pConn, char szBuff[], int nBufferSize) {
    int     nResult     = -1;
    int     nRetCode    = -1;
    int     nRevLen     = 0;

    if (pConn->uRecvBuffPos > 0) {
        size_t  nSumLen     = pConn->uRecvBuffPos;
        char*   pbyStart    = pConn->byRecvBuffer;
        size_t  nRecivedLen = 0;

        nRevLen = (int)pConn->uRecvBuffPos;

		for (size_t i = pConn->uLastCheckPos; i < nRevLen; i++)
			if (*(pbyStart + i) == '\n') {
				size_t nSubLen = nRecivedLen + i + 1;
                if (nSubLen < nBufferSize) {
                    memcpy(szBuff, pbyStart, nSubLen);
                    szBuff[nSubLen] = '\0';
                }
				memmove(pConn->byRecvBuffer, pbyStart + nSubLen, nSumLen - nSubLen);
				pConn->uRecvBuffPos = nSumLen - nSubLen;

                nResult = (int)nSubLen;
                pConn->uLastCheckPos = 0;
                goto exit;
			}

        pConn->uLastCheckPos = nSumLen;
    }

    nRevLen = recv(pConn->nSocket,
        (char*)pConn->byRecvBuffer + pConn->uRecvBuffPos, 
        (int)(sizeof(pConn->byRecvBuffer) - pConn->uRecvBuffPos - 1), 0
    );

    if (nRevLen < 0)
        goto exit;

    if (nRevLen > 0) {
        size_t  nSumLen    = pConn->uRecvBuffPos + nRevLen;
        char*   pbyStart    = pConn->byRecvBuffer + pConn->uRecvBuffPos;
        size_t  nRecivedLen = pConn->uRecvBuffPos;
        
        pConn->uRecvBuffPos = nSumLen;

        for (int i = 0; i < nRevLen; i++)
            if (*(pbyStart + i) == '\n') {
                size_t nSubLen = nRecivedLen + i + 1;
				if (nSubLen < nBufferSize) {
					memcpy(szBuff, pbyStart, nSubLen);
					szBuff[nSubLen] = '\0';
				}
                memmove(pConn->byRecvBuffer, pbyStart + nSubLen, nSumLen - nSubLen);
                pConn->uRecvBuffPos = nSumLen - nSubLen;
                nResult = (int)nSubLen;
                pConn->uLastCheckPos = 0;
                goto exit;
            }
        pConn->uLastCheckPos = nSumLen;
    }

    nResult = 0;

exit:
    return nResult;
}
```

## 错误分析

该函数中有两个错误，第一个错误是这段代码。

```c++
if (nSubLen < nBufferSize) {
	memcpy(szBuff, pbyStart, nSubLen);
	szBuff[nSubLen] = '\0';
}
memmove(pConn->byRecvBuffer, pbyStart + nSubLen, nSumLen - nSubLen);
pConn->uRecvBuffPos = nSumLen - nSubLen;
```

如果 `nSubLen > nBufferSize`, 就会直接走下面的内存移动逻辑，导致 `pConn->byRecvBuffer[pbyStart]` 到 `pConn->byRecvBuffer[pbyStart + nSubLen]` 这一段内存会丢失。但是这个 bug 和上面的错误无关，只是有丢失数据的风险。

第二个错误也是这段代码。

```c++
        size_t  nSumLen    = pConn->uRecvBuffPos + nRevLen;
        char*   pbyStart    = pConn->byRecvBuffer + pConn->uRecvBuffPos;
        
        pConn->uRecvBuffPos = nSumLen;

        for (int i = 0; i < nRevLen; i++)
            if (*(pbyStart + i) == '\n') {
                size_t nSubLen = nRecivedLen + i + 1;
				if (nSubLen < nBufferSize) {
					memcpy(szBuff, pbyStart, nSubLen);
					szBuff[nSubLen] = '\0';
				}
                memmove(pConn->byRecvBuffer, pbyStart + nSubLen, nSumLen - nSubLen);
                pConn->uRecvBuffPos = nSumLen - nSubLen;
				// ... ...
            }
    }
```

在代码中, `pbyStart` 设置为了

```c++
char*   pbyStart    = pConn->byRecvBuffer + pConn->uRecvBuffPos;
```

这个地址，这就会导致在代码

```c++
memcpy(szBuff, pbyStart, nSubLen);
```

中复制内存的时候，遗忘了从 导致 `pConn->byRecvBuffer[0]` 到 `pConn->byRecvBuffer[pConn->uRecvBuffPos]` 这段内存，所以向外返回的字符串就是错误的，

下面的 `memmove` 移动的内存也是错误的。

应该改成

``` c++
        size_t  nSumLen    = pConn->uRecvBuffPos + nRevLen;
        char*   pbyStart    = pConn->byRecvBuffer + pConn->uRecvBuffPos;
        
        pConn->uRecvBuffPos = nSumLen;

        for (int i = 0; i < nRevLen; i++)
            if (*(pbyStart + i) == '\n') {
                size_t nSubLen = nRecivedLen + i + 1;
				if (nSubLen < nBufferSize) {
					memcpy(szBuff, pConn->byRecvBuffer, nSubLen);
					szBuff[nSubLen] = '\0';
				}
                memmove(pConn->byRecvBuffer, pConn->byRecvBuffer + nSubLen, nSumLen - nSubLen);
                pConn->uRecvBuffPos = nSumLen - nSubLen;
				// ... ...
            }
    }
```

