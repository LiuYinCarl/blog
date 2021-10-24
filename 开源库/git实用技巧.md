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

## git 暂存区的概念

可以通过 `git add` 命令将文件存入 git 暂存区。

存入到了 git 暂存区中的文件在没有再次修改之前不会在 `git diff` 的输出中出现。如果存入了暂存区之后再次修改了这个文件，那么 `git diff` 的输出也只会展示存入了暂存区后的修改内容。

## git 按单词进行差异比较

git 默认是基于行进行差异比较的。如果我们想要看基于单词的比较的话，可以使用如下命令。

```bash
git diff --word-diff
```

但是这样不能看到暂存区中的变更，如果想看到添加到暂存区中的文件的变更，可以使用如下命令。

```bash
git diff --cached --word-diff
```

下面是一个具体的例子。

```bash
➜ mkdir test
➜ cd test/
➜ git init
Initialized empty Git repository in /Users/zhl/dev/test/git/test/.git/
➜ touch a.txt
➜ echo "when where how" > a.txt
➜ git add a.txt
➜ git diff
➜ echo "when you how" > a.txt
➜ git add a.txt
➜ git diff # 存入暂存区后，看不到差异
➜ echo "when you me" > a.txt
➜ git diff --word-diff
diff --git a/a.txt b/a.txt
index 9d4e288..0ad843e 100644
--- a/a.txt
+++ b/a.txt
@@ -1 +1 @@
when you [-how-]{+me+}
➜ git diff --cached --word-diff # 使用 --cached 可以看到暂存区中的差异了
diff --git a/a.txt b/a.txt
new file mode 100644
index 0000000..9d4e288
--- /dev/null
+++ b/a.txt
@@ -0,0 +1 @@
{+when you how+}
```



## 用 git stash 临时保存进度

 在开发一个功能开发到一半的过程中需要紧急处理另一个 bug 的时候，需要将未开发完成的功能临时进程保存，恢复一个没有修改的工作区，或者切换到其他分支进行 bug 修复。

下面是一个具体的例子。

```bash
➜ mkdir test
➜ cd test/
➜ git init
Initialized empty Git repository in /Users/zhl/dev/test/git/test/.git/
➜ echo "when where how" > a.txt # 创建一个有一行的文件
➜ git add -A
➜ git commit -m "add a.txt" # 提交这个文件
[main (root-commit) 5912fc5] add a.txt
 1 file changed, 1 insertion(+)
 create mode 100644 a.txt
➜ echo "when you how" > a.txt # 修改第一行，模拟开发一个功能到一半
➜ git stash # 处理其他bug,将未完成的功能的修改暂存
Saved working directory and index state WIP on main: 5912fc5 add a.txt
➜ git status # 查看状态，发现修改被暂存，工作区变干净了
On branch main
nothing to commit, working tree clean
➜ echo "add line 2" >> a.txt # 添加第二行，模拟修复bug
➜ cat a.txt
when where how
add line 2
➜ git add -A
➜ git commit -m "add line 2" # 提交bug修复代码
[main 76f297c] add line 2
 1 file changed, 1 insertion(+)
➜ git stash pop # 将暂存的文件取出，发现出现了冲突
Auto-merging a.txt
CONFLICT (content): Merge conflict in a.txt
The stash entry is kept in case you need it again.
➜ cat a.txt # 查看冲突
<<<<<<< Updated upstream
when where how
add line 2
=======
when you how
>>>>>>> Stashed changes
➜  test git:(main) ✗ emacs a.txt # 手动合并冲突
➜  test git:(main) ✗ git stash drop # 删除最近的一个 stash
Dropped refs/stash@{0} (5d47bf44053352dc2546e7df39a39440b641eab9)
➜  test git:(main) ✗ git add -A # 将之前开发的部分功能加到暂存区
➜  test git:(main) ✗ em a.txt # 将第一行改成 "when you me",模拟继续开发功能
➜  test git:(main) ✗ git diff
diff --git a/a.txt b/a.txt
index 97f50a5..13fef9d 100644
--- a/a.txt
+++ b/a.txt
@@ -1,2 +1,2 @@
-when you how
+when you me
 add line 2
➜ git add -A
➜ git commit -m "modify line 1" # 提交开发完成的功能
[main 4b97569] modify line 1
 1 file changed, 1 insertion(+), 1 deletion(-)
➜ git log
commit 4b975698536fea6b2b66bc0e4fe0675097711875 (HEAD -> main)
Author: LiuYinCarl <1427518212@qq.com>
Date:   Sun Oct 24 21:23:02 2021 +0800

    modify line 1

commit 76f297c168d0d2e4fdcfd041e793509333774be6
Author: LiuYinCarl <1427518212@qq.com>
Date:   Sun Oct 24 21:15:05 2021 +0800

    add line 2

commit 5912fc5d54f9970127e862d394903aa2d99c3fa1
Author: LiuYinCarl <1427518212@qq.com>
Date:   Sun Oct 24 21:13:24 2021 +0800

    add a.txt
➜ cat a.txt # 查看内容
when you me
add line 2
```



## git 的配置文件

git 有三个优先级不同的配置文件。

- 项目级别的配置文件，在项目的  `.git/config` 位置
- 用户级别的配置文件，在 `~/.gitconfig` 位置
- 系统级别的配置文件，在 `/etc/gitconfig` 位置

三个配置文件的优先级依次降低。

- 进行项目级别的配置，使用的命令是 `git config`。

- 进行用户级别的配置，使用的命令是 `git config --global`。

- 进行系统级别的配置，使用的命令是 `git config --system`。



## 修改错误的提交者信息

有些时候，如果没有设置项目的作者就进行了提交，会导致提交者信息出现错误，所以 git 提供了命令来进行提交者信息的修改。

下面是一个修改最近一次提交的 author 信息的例子。

```bash
➜ git init test
Initialized empty Git repository in /Users/zhl/dev/test/git/test/.git/
➜ cd test/
# 配置一个错误的 author 信息
➜ git config user.name "wrong name"
➜ git config user.email "wrong email"
➜ touch a.txt
➜ git add -A
➜ git commit -m "commit by wrong author info"
[main (root-commit) ba2de4c] commit by wrong author info
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 a.txt
➜ git log # 查看提交记录，发现 author 信息错误
commit ba2de4c567cf2696bdf6be0719ff6b6e02646422 (HEAD -> main)
Author: wrong name <wrong email>
Date:   Mon Oct 25 05:38:27 2021 +0800

    commit by wrong author info
# 配置正确的 author 信息
➜ git config user.name "right name"
➜ git config user.email "right email"
# 使用 --amend --reset-author 重制最近一次提交的 author 信息
➜ git commit --amend --reset-author
[main 78b6b11] commit by right author info
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 a.txt
➜  test git:(main) git log
commit 78b6b11363a58319111e259118e8f66ef3a3101a (HEAD -> main)
Author: right name <right email>
Date:   Mon Oct 25 05:39:16 2021 +0800

    commit by right author info
```



## git diff 的几个参数说明

对于一个 git 仓库某个分支中的文件，最多会有三个不同的版本(不考虑 git stash)：版本库中的版本，暂存区 stage 中的版本，工作区中的版本。

`git diff` 比较的是工作区和暂存区的差异。`git diff HEAD` 比较的是工作区和版本库当前分支的差异。`git diff --cache` 或者 `git diff --staged`比较的是暂存区 stage 和版本库当前分支的差异。
