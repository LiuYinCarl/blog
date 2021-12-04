# ssh-keygen 使用

ssh-keygen 是用来生成 ssh密钥的工具，最简单的使用场景场景是 git 的 ssh 免密码登录。

下面简单的介绍下 ssh-keygen 的常见使用方式。



## ssh-keygen 用法

``` bash
➜  github ssh-keygen --help
usage: ssh-keygen [-q] [-b bits] [-C comment] [-f output_keyfile] [-m format]
                  [-t dsa | ecdsa | ecdsa-sk | ed25519 | ed25519-sk | rsa]
                  [-N new_passphrase] [-O option] [-w provider]
       ssh-keygen -p [-f keyfile] [-m format] [-N new_passphrase]
                   [-P old_passphrase]
       # 这个 -f 命令可以指定文件名，设置了这个参数等下就不会再交互式让你确认文件名了，这个参数可以用来写脚本的时候自动指定 ssh key 文件名
       ssh-keygen -i [-f input_keyfile] [-m key_format]
       ssh-keygen -e [-f input_keyfile] [-m key_format]
       ssh-keygen -y [-f input_keyfile]
       # -c 命令可以用来给这个 ssh key 加一点备注，默认会跟在 ssh key 的后面，这样子可以帮助你记住这个 ssh key 是用来干嘛的
       ssh-keygen -c [-C comment] [-f keyfile] [-P passphrase]
       ssh-keygen -l [-v] [-E fingerprint_hash] [-f input_keyfile]
       ssh-keygen -B [-f input_keyfile]
       ssh-keygen -D pkcs11
       ssh-keygen -F hostname [-lv] [-f known_hosts_file]
       ssh-keygen -H [-f known_hosts_file]
       ssh-keygen -K [-w provider]
       ssh-keygen -R hostname [-f known_hosts_file]
       ssh-keygen -r hostname [-g] [-f input_keyfile]
       ssh-keygen -M generate [-O option] output_file
       ssh-keygen -M screen [-f input_file] [-O option] output_file
       ssh-keygen -I certificate_identity -s ca_key [-hU] [-D pkcs11_provider]
                  [-n principals] [-O option] [-V validity_interval]
                  [-z serial_number] file ...
       ssh-keygen -L [-f input_keyfile]
       ssh-keygen -A [-f prefix_path]
       ssh-keygen -k -f krl_file [-u] [-s ca_public] [-z version_number]
                  file ...
       ssh-keygen -Q -f krl_file file ...
       ssh-keygen -Y find-principals -s signature_file -f allowed_signers_file
       ssh-keygen -Y check-novalidate -n namespace -s signature_file
       ssh-keygen -Y sign -f key_file -n namespace file ...
       ssh-keygen -Y verify -f allowed_signers_file -I signer_identity
                -n namespace -s signature_file [-r revocation_file]
```



## 生成密钥

``` bash
# 输入这个命令，然后会提示你输入文件名，如果之前生成过默认的 ssh key 文件，那么最好指定另外一个名字，避免原来的 ssh key 被覆盖
# 输入完文件名后，会提示设置密码和确认密码，可以直接回车不设置密码
$ ssh-keygen
```

使用 `ssh-kengen` 会在~/.ssh/目录下生成两个文件，不指定文件名和密钥类型的时候，默认生成的两个文件是 `id_rsa` 和 `id_rsa.pub`，分别是私钥和公钥。私钥是你自己要保留的，公钥是给其他人的。



## 将公钥添加到远程服务器上

```bash
ssh-copy-id -i 公钥文件 username@远程服务器IP
# 这个命令会让远程服务器将你上面生成的公钥文件添加到 ~/.ssh/authorized_keys 文件中
# 如果生成的公钥是准备给 gitlab/github 使用的，可以找一下网上的教程看一下在网页上哪个位置添加
# 如果你的服务器默认的SSH 修改了的话，还需要注意需要指定 -p port 参数来设置 SSH 端口
```



## 测试连接

```bash
ssh -T user@+host
# 比如你将公钥添加到github 的账户中后，测试连接的方法是
ssh -T git@github.com
```



## 如果使用的 ssh key 文件的名字不是默认的 id_ras

如果自定义了 ssh 密钥名字，需要再设置一下 ssh 的配置文件，不然连接 ssh 时还会使用默认的密钥文件，导致拒绝连接。

如果不想修改配置文件的话，使用下面这个命令也是可以的，但是每次 ssh 连接都这样操作很麻烦。

```bash
ssh -T -i 你的私钥文件 git@github.com
```

修改配置文件的方式：

```bash
# 编辑配置文件
vim /etc/ssh/ssh_config

# 在 Host * 配置下添加配置
Host github.com
HostName github.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/git_test
```



## 参考

[ssh-keygen 基本用法](https://www.liaohuqiu.net/cn/posts/ssh-keygen-abc/)

[创建SSH密钥时使用了自定义文件名遇到的问题](https://blog.csdn.net/weixin_43670802/article/details/105527914)

[Git配置多个SSH KEY](https://www.jianshu.com/p/9c06e8de3eba)

[使用ssh生成密钥并保存在不同的文件（ubuntu）](https://www.cnblogs.com/liuqd001/p/9705028.html)