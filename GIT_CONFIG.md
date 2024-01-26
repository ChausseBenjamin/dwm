# This is how I will remain in sync with upstream

```ini
[core]
  repositoryformatversion = 0
  filemode = true
  bare = false
  logallrefupdates = true
[remote "origin"]
  url = git@github.com:ChausseBenjamin/dwm.git
  fetch = +refs/heads/*:refs/remotes/origin/*
[branch "master"]
  remote = upstream
  merge = refs/heads/master
[branch "personal"]
  remote = origin
  merge = refs/heads/personal
[remote "upstream"]
  url = git://git.suckless.org/dwm
  fetch = +refs/heads/*:refs/remotes/upstream/*
```
