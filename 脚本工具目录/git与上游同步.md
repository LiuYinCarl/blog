# git 与上游同步

在给开源项目提交 Pull Request 的时候，需要先 fork 下来，再修改，然后再将修改推送给上游。如果 fork 与 推送之间间隔的时间比较长，上游可能已经发生了修改，所以在推送修改之前，需要先同步下上游的代码，看看我们 fork 的分支和上游的分支是否存在冲突。

具体操作如下：

```bash
# 给自己 fork 的仓库添加上游仓库
git remote add upstream 上游仓库的地址

# 查看是否添加成功
git remote -v

# 拉取上游的修改
git fetch upstream

# 合并 也可以使用 merge, 但是使用了 merge 会有 merge 记录
# 下游同步上游修改最好使用 rebase
# 上游接受下游提交最好使用 merge
git rebase upstream/main

# 更新自己的远程仓库
git push origin main

# 最后，可以在 github 上你的 fork 的主页找到提交 PR 的按钮
```
