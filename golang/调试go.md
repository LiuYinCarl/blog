# 调试 golang

要调试 golang 的源代码，需要先编译一下 golang

[编译golang的方法](https://segmentfault.com/a/1190000009594143)

完整命令

``` bash
echo "export GOROOT=$HOME/.golang/go" >> ~/.bash_profile
echo "export GOPATH=$HOME/.golang/path" >> ~/.bash_profile
echo "export PATH=$PATH:$HOME/.golang/go/bin" >> ~/.bash_profile
echo "export GOROOT_BOOTSTRAP=$HOME/.golang/go1.4" >> ~/.bash_profile
source ~/.bash_profile
cd ~
mkdir .golang
git clone https://github.com/golang/go.git go
cp -r go go1.4
cd go1.4
git checkout -b release-branch.go1.4 origin/release-branch.go1.4
cd src
./make.bash
cd ../../go
git checkout -b release-branch.go1.8 origin/release-branch.go1.8
cd src
./make.bash
go version
```



但是如果操作系统中本来就有 go 编译器的话，我觉得是可以直接使用 go 编译器的,没有必要非得用 go1.4 来编译。