# 静态编译OpenSSL和curl

## 1 静态编译 OpenSSL

在 github(https://github.com/openssl/openssl/tags) 上下载合适的 OpenSSL 版本,
这里选择 OpenSSL_1_1_1m

```bash
# 下载 OpenSSL
wget https://github.com/openssl/openssl/archive/refs/tags/OpenSSL_1_1_1m.tar.gz

# 解压
tar -zxf OpenSSL_1_1_1m.tar.gz

# 进入解压后的目录
cd openssl-OpenSSL_1_1_1m/

# 配置 --prefix=/data/test/ssl_test2/openssl 是要自己设置的安装目录
./config --prefix=/data/test/ssl_test2/openssl -fPIC no-shared

# 编译
make

# 安装到/data/test/ssl_test2/openssl
make install 
```

## 2 静态编译 curl

在github(https://github.com/curl/curl/tags) 或者官网(https://curl.se/download/)下载合适的 curl 版本,
这里选择 curl-7.62.0 

```bash
# 下载 curl
wget https://curl.se/download/curl-7.62.0.tar.gz

# 解压
tar -zxf curl-7.62.0.tar.gz

# 进入解压后的目录
cd cd curl-7.62.0

# 配置 /data/test/ssl_test2/curl 是要自己设置的安装目录
./configure --prefix=/data/test/ssl_test2/curl --with-ssl=/data/test/ssl_test2/openssl --disable-shared

# 编译
make

# 安装到 /data/test/ssl_test2/curl
make install
```

## 参考

[Linux下OpenSSL静态库编译及使用](https://www.linuxidc.com/Linux/2017-09/147117.htm)

