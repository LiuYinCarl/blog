## 参考代码

> [Linux ping 简单实现](https://blog.csdn.net/tuantuanlin/article/details/17006867)



## 实现

``` c
//mysock.h
#ifndef MYSOCK_H_H
#define MYSOCK_H_H

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>/*protocol参数形如IPPROTO_XXX的常值*/
#include <netinet/ip.h>/*ip帧头定义*/
#include <netinet/ip_icmp.h>/*icmp帧头定义*/
#include <signal.h>/*信号处理*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>/*recvfrom() & sendto()*/
#include <sys/time.h>/*gettimeofday()*/
#include <time.h>
#include <unistd.h>

#define PERIOD      3
#define MAXLINE     2048
#define DEFAULT_LEN 56

#define uchar   unsigned char
#define uint    unsigned int
#define ushort  unsigned short

#endif  // MYSOCK_H_H

uchar sendBuf[MAXLINE];
uchar recvBuf[MAXLINE];
struct sockaddr_in destAddr;
uint seq = 0;
int sockfd;

void alarm_send(int signo);
void send_pack();
void receive_pack(int sockfd);
void icmp_pack();
ushort checksum(uchar* buf, uint len); //对每16位进行反码求和（高位溢出位会加到低位），即先对每16位求和，在将得到的和转为反码

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s IP\n", argv[0]);
        exit(1);
    }
    if ((sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket error:");
        exit(1);
    }

    memset(&destAddr, 0, sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &destAddr.sin_addr);

    //信号处理
    struct sigaction newact, oldact;
    newact.sa_handler = alarm_send;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);
    alarm(PERIOD);

    receive_pack(sockfd);
}

// 构造 ICMP 数据包
void icmp_pack()
{
    int i;
    struct icmp* icmp;
    pid_t pid = getpid();
    memset(sendBuf, 0, MAXLINE);
    icmp = (struct icmp*)sendBuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_cksum = 0;
    icmp->icmp_id = pid;
    icmp->icmp_seq = seq++;
    struct timeval* tvstart;
    tvstart = (struct timeval*)icmp->icmp_data;
    gettimeofday(tvstart, NULL);
    icmp->icmp_cksum = checksum((uchar*)icmp, DEFAULT_LEN + 8);
}

// 发送 ICMP 数据包
void send_pack()
{
    icmp_pack();
    sendto(sockfd, sendBuf, DEFAULT_LEN + 8, 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
}

// 接收 ICMP 数据包
void receive_pack(int sockfd)
{
    int n = 0;
    struct ip* p_ip;
    struct icmp* p_icmp;
    ushort len_iphd, len_icmp;
    char ip_source[INET_ADDRSTRLEN];
    ushort sum_recv, sum_cal;
    struct timeval *tvstart, *tvend;
    tvend = malloc(sizeof(sizeof(struct timeval)));
    double delt_sec;

    while (1) {
        memset(recvBuf, 0, MAXLINE);
        n = recvfrom(sockfd, recvBuf, MAXLINE, 0, NULL, NULL); //接收通过网卡的信息。
        if (n < 0) {
            if (errno == EINTR) //interrupted system call
                continue;
            else {
                perror("recvform error");
                exit(1);
            }
        }
        gettimeofday(tvend, NULL);

        p_ip = (struct ip*)recvBuf;
        len_iphd = (p_ip->ip_hl) * 4;

        len_icmp = ntohs(p_ip->ip_len) - len_iphd;

        p_icmp = (struct icmp*)((uchar*)p_ip + len_iphd); //从 IP 数据报中获取 ICMP 数据包头部 必须强制转换
        sum_recv = p_icmp->icmp_cksum;
        p_icmp->icmp_cksum = 0;

        sum_cal = checksum((uchar*)p_icmp, len_icmp);  // 对收到的 ICMP 包进行校验
        if (sum_cal != sum_recv) {
            printf("checksum error\tsum_recv = %d\tsum_cal = %d\n", sum_recv, sum_cal);
        } else {
            switch (p_icmp->icmp_type) {
                case ICMP_ECHOREPLY: {
                    pid_t pid_now, pid_rev;
                    pid_rev = (p_icmp->icmp_id);
                    pid_now = getpid();
                    if (pid_rev != pid_now) {
                        printf("pid not match!pin_now = %d, pin_rev = %d\n", pid_now, pid_rev);
                    }
                    inet_ntop(AF_INET, (void*)&(p_ip->ip_src), ip_source, INET_ADDRSTRLEN);
                    tvstart = (struct timeval*)p_icmp->icmp_data;
                    delt_sec = (tvend->tv_sec - tvstart->tv_sec) + (tvend->tv_usec - tvstart->tv_usec) / 1000000.0;
                    printf("%d bytes from %s: icmp_req=%d ttl=%d time=%4.2f ms\n", len_icmp, ip_source, p_icmp->icmp_seq, p_ip->ip_ttl, delt_sec * 1000); //想用整型打印的话必须强制转换！
                    break;
                }
                case ICMP_TIME_EXCEEDED: {
                    printf("time out!\n");
                    break;
                }
                case ICMP_DEST_UNREACH: {
                    inet_ntop(AF_INET, (void*)&(p_ip->ip_src), ip_source, INET_ADDRSTRLEN);
                    printf("From %s icmp_seq=%d Destination Host Unreachable\n", ip_source, p_icmp->icmp_seq);
                    break;
                }
                case ICMP_ECHO: {
                    printf("catch a icmp Echo Request pack\n");
                    break;
                }
                default: {
                    printf("unexcept icmp pack type: %d\n", p_icmp->icmp_type);
                }
            }
        }
    }
}

// 计算 ICMP 数据包校验和， 对整个报文进行校验
ushort checksum(uchar* buf, uint len) //对每16位进行反码求和（高位溢出位会加到低位），即先对每16位求和，在将得到的和转为反码
{
    unsigned long sum = 0;
    ushort* pbuf;
    pbuf = (ushort*)buf; //转化成指向16位的指针
    while (len > 1) //求和
    {
        sum += *pbuf++;
        len -= 2;
    }
    if (len) //如果len为奇数，则最后剩一位要求和
        sum += *(uchar*)pbuf;
    sum = (sum >> 16) + (sum & 0xffff); //
    sum += (sum >> 16); //上一步可能产生溢出
    return (ushort)(~sum);
}

// 信号处理函数
void alarm_send(int signo)
{
    send_pack();
    alarm(PERIOD);
    return;
}
```



## 测试

**tips**

_编译该代码后需要在 root 权限下才可以执行_

**测试 IP：47.93.196.173 **

``` bash
[carl-pc test]# ./myping 47.93.196.173
64 bytes from 47.93.196.173: icmp_req=0 ttl=52 time=24.63 ms
64 bytes from 47.93.196.173: icmp_req=1 ttl=52 time=24.48 ms
64 bytes from 47.93.196.173: icmp_req=2 ttl=52 time=24.36 ms
^C
```

**测试 IP： 47.93.196.999**

``` bash
[carl-pc test]# ./myping 47.93.196.999
catch a icmp Echo Request pack
64 bytes from 127.0.0.1: icmp_req=0 ttl=64 time=0.10 ms
catch a icmp Echo Request pack
64 bytes from 127.0.0.1: icmp_req=1 ttl=64 time=0.07 ms
catch a icmp Echo Request pack
64 bytes from 127.0.0.1: icmp_req=2 ttl=64 time=0.07 ms
^C
```

ping `47.93.196.999` 会由于 IP 地址不合规 导致 `destAddr.sin_addr` 变为 0, 也就是 本地环回地址。

收到 `echo request` 包的原因是 ping 的是本地环回地址，代码里面收到了一次自己发出去的包。
