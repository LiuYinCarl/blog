# git 技巧



## 修改 git 的默认编辑器

```bash
git config core.editor vim
```

将 git 的默认编辑器修改为 vim。



## 将 git 部分命令的输出中的中文从八进制改成中文

针对部分命令如 `git log`  `git status` 中含中文的路径名会以八进制显示的情况，可以进行如下设置，让 git 以中文显示路径。

```bash
git config --global core.quotepath false
```



## 按条件查看提交历史

[2.3 Git 基础 - 查看提交历史](https://git-scm.com/book/zh/v2/Git-%E5%9F%BA%E7%A1%80-%E6%9F%A5%E7%9C%8B%E6%8F%90%E4%BA%A4%E5%8E%86%E5%8F%B2)

查看提交历史使用的命令是 `git log`。下面介绍几个常用的选项。

```bash
git log -2 # 输出最近的两次提交
git log -p 2 # 按 patch 格式输出最近的两次提交
git log --since 2021-01-01 # 输出 2021-01-01 之后的提交
git log --until 2021-01-01 # 输出最晚到 2021-01-01 的提交
git log --author carl  # 输出作者字符串中包含 "carl" 的提交
git log --committer carl # 输出提交者字符串中包含 "carl" 的提交
git log --grep carl # 输出提交说明中包含 "carl" 的提交
git log -S carl # 输出提交的内容中添加或删除了该字符串的提交，例如可以用来查看函数的改动
```



## 重写提交说明

当执行了 `git commit "some message"` 命令之后发现提交的 "some message"  存在问题，需要修改，可以下列操作来修改提交信息。

如果要修改的是**最近一次** `git commit` 的提交信息，使用如下修补提交的命令。

```bash
git commit --amend
```

执行这条命令后就会打开一个 Nano 的编辑窗口，然后就可以修改上一次的提交信息了。

如果不想打开 Nano，可以使用 `-m` 参数加上新的提交信息。

```bash
git commit --amend -m "new commit message"
```

如果需要修改的是历史提交信息（即不是最近一次提交信息）的话，就需要使用 `git rebase` 命令，下面是一个完整的例子。

```bash
➜ mkdir test1
➜ cd test1/
➜ git init
Initialized empty Git repository in /home/lzh/test/git/test1/.git/
➜ touch a.txt
➜ git add -A
➜ git commit -m "create a.txt"
[master (root-commit) 39d83ee] create a.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 a.txt
➜ touch b.txt
➜ git add -A
➜ git commit -m "create b.txt"
[master 8958708] create b.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 b.txt
➜ git log
commit 895870830338c9fcd3700fe0c4da98747ef6fd7b (HEAD -> master)
Author: LiuYinCarl <bearcarl@qq.com>
Date:   Wed Oct 20 20:50:53 2021 +0800

    create b.txt

commit 39d83eec2dc0aa84bc5b921b4c81524c29345504
Author: LiuYinCarl <bearcarl@qq.com>
Date:   Wed Oct 20 20:50:30 2021 +0800

    create a.txt
```

`git rebase -i` 后接的参数如果是 `--root` 表示从第一个提交记录开始查看。如果是一个提交记录的散列值，比如 `39d83eec2dc0aa84bc5b921b4c81524c29345504` 则表示从该提交记录开始查看，不包含这个提交。

这是是 执行 `rebase` 命令后打开的文件。从上到下一次是我们的提交记录。

```bash
pick 39d83ee create a.txt
pick 8958708 create b.txt

# Rebase 8958708 onto 009e0bc (2 commands)
#
# Commands:
# p, pick <commit> = use commit
# r, reword <commit> = use commit, but edit the commit message
# e, edit <commit> = use commit, but stop for amending
# s, squash <commit> = use commit, but meld into previous commit
# f, fixup <commit> = like "squash", but discard this commit's log message
# x, exec <command> = run command (the rest of the line) using shell
# b, break = stop here (continue rebase later with 'git rebase --continue')
# d, drop <commit> = remove commit
# l, label <label> = label current HEAD with a name
# t, reset <label> = reset HEAD to a label
# m, merge [-C <commit> | -c <commit>] <label> [# <oneline>]
# .       create a merge commit using the original merge commit's
# .       message (or the oneline, if no original merge commit was
# .       specified). Use -c <commit> to reword the commit message.
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
```

根据命令提示，修改成下面这个样子, 第一行改成 r，表示我们要修改这次历史提交的提交信息。

```bash
r 39d83ee create a.txt
pick 8958708 create b.txt

# Rebase 8958708 onto 009e0bc (2 commands)
# 未修改部分，省略 ...
```

保存退出后，git 会自动打开另一个编辑页面，让你编辑这次历史提交的提交信息，内容如下

```bash
create a.txt

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# Date:      Wed Oct 20 20:50:30 2021 +0800
#
# interactive rebase in progress; onto 009e0bc
# Last command done (1 command done):
#    r 39d83ee create a.txt
# Next command to do (1 remaining command):
#    pick 8958708 create b.txt
# You are currently editing a commit while rebasing branch 'master' on '009e0bc'.
#
#
# Initial commit
#
# Changes to be committed:
#       new file:   a.txt
#
```

最上面一行就是我们之前的提交信息，现在将它改成下面这个样子

```bash
create rebase commit

# 未修改部分，省略 ...

```

保存退出

```bash
➜ git rebase -i --root
[detached HEAD 1c19a3b] create rebase commit
 Date: Wed Oct 20 20:50:30 2021 +0800
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 a.txt
Successfully rebased and updated refs/heads/master.
➜ git log
commit c771c4b14d78f6779cb6b77615562cf8ea65206d (HEAD -> master)
Author: LiuYinCarl <bearcarl@qq.com>
Date:   Wed Oct 20 20:50:53 2021 +0800

    create b.txt

commit 1c19a3b8a5d60b6af9b8c87a6ac1aeecaac65727
Author: LiuYinCarl <bearcarl@qq.com>
Date:   Wed Oct 20 20:50:30 2021 +0800

    create rebase commit
```

通过 `git log` 命令可以看到第一次提交的 commit 信息发生了变化。



## 去除错误提交的文件

如果是要删除最近一次提交的话，可以使用 `git rm` 和 `git commit` 命令。

```bash
➜ mkdir testrm
➜ cd testrm/
➜ git init
Initialized empty Git repository in /Users/zhl/dev/test/git/testrm/.git/
➜ touch a.txt b.txt
➜ git add -A
➜ git commit -m "add two file"
[master (root-commit) 01a8038] add two file
 Committer: ZH L <zhl@ZHdeMacBook-Air.local>
 2 files changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 a.txt
 create mode 100644 b.txt
➜ git log -p
commit 01a80384a8c60881d9ffb72b9f4cada684468474 (HEAD -> master)
Author: ZH L <zhl@ZHdeMacBook-Air.local>
Date:   Sat Oct 23 00:55:35 2021 +0800

    add two file

diff --git a/a.txt b/a.txt
new file mode 100644
index 0000000..e69de29
diff --git a/b.txt b/b.txt
new file mode 100644
index 0000000..e69de29
➜ git rm --cached a.txt
rm 'a.txt'
➜ git commit --amend
[master ca0da34] add two file
 Date: Sat Oct 23 00:55:35 2021 +0800
 Committer: ZH L <zhl@ZHdeMacBook-Air.local>
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 b.txt
➜ git log -p
commit ca0da344170a84afe1f5ecfe3b01223db536613f (HEAD -> master)
Author: ZH L <zhl@ZHdeMacBook-Air.local>
Date:   Sat Oct 23 00:55:35 2021 +0800

    add two file

diff --git a/b.txt b/b.txt
new file mode 100644
index 0000000..e69de29
```

可以看到，使用 `git rm --cached a.txt` 和 `git commit --amend` 后成功地从提交记录中删除了之前提交的 `a.txt` 文件。

如果需要修改文件的不是最近一次提交，而是历史提交记录，则需要使用 `rebase` 操作。

 ```bash
 ➜ mkdir test
 ➜ cd test/
 ➜ git init
 Initialized empty Git repository in /Users/zhl/dev/test/git/test/.git/
 ➜ touch a.txt b.txt
 ➜ git add -A
 ➜ git commit -m "add a.txt b.txt"
 [main (root-commit) 9a4b1c4] add a.txt b.txt
  2 files changed, 0 insertions(+), 0 deletions(-)
  create mode 100644 a.txt
  create mode 100644 b.txt
 ➜ touch c.txt
 ➜ git add -A
 ➜ git commit -m "add c.txt"
 [main 82f1a7c] add c.txt
  1 file changed, 0 insertions(+), 0 deletions(-)
  create mode 100644 c.txt
 ➜  test git:(main) git log
 commit 82f1a7c929007fbc175d2164f700ca46a324c45c (HEAD -> main)
 Author: LiuYinCarl <1427518212@qq.com>
 Date:   Sat Oct 23 01:23:36 2021 +0800
 
     add c.txt
 
 commit 9a4b1c4bd21c963722cfd29aefb9e95fa3f054bf
 Author: LiuYinCarl <1427518212@qq.com>
 Date:   Sat Oct 23 01:23:05 2021 +0800
 
     add a.txt b.txt
 ➜  test git:(main) git rebase -i --root
 ```

执行 `git rebase` 后，会打开一个文件，内容如下（省略操作提示行）

```bash
pick 9a4b1c4 add a.txt b.txt
pick 82f1a7c add c.txt
```

根据提示，使用 `edit` 命令将提交记录修改为如下

```bash
edit 9a4b1c4 add a.txt b.txt
pick 82f1a7c add c.txt
```

然后继续在终端执行如下命令

```bash
➜ git rebase -i --root
Stopped at 9a4b1c4...  add a.txt b.txt
You can amend the commit now, with

  git commit --amend

Once you are satisfied with your changes, run

  git rebase --continue
➜ git rm --cached a.txt
rm 'a.txt'
➜ git commit --amend -m "add b.txt"
[detached HEAD 4729a73] add b.txt
 Date: Sat Oct 23 01:23:05 2021 +0800
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 b.txt
➜ git rebase --continue
Successfully rebased and updated refs/heads/main.
➜ git log
commit 4f59d2381da0f791649d413718fd1c81f5248da0 (HEAD -> main)
Author: LiuYinCarl <1427518212@qq.com>
Date:   Sat Oct 23 01:23:36 2021 +0800

    add c.txt

commit 4729a73942ef9be65953d9f1e0148b6979528b85
Author: LiuYinCarl <1427518212@qq.com>
Date:   Sat Oct 23 01:23:05 2021 +0800

    add b.txt
```

可以看到，提交记录已经发生了变化，原先错误提交的 `a.txt` 也被从提交记录中去除了。
