# inotify and epoll

![dir and base name](../pngs/base_dir_name.png)

```shell
gcc -o inotify inotify.c
mkdir tmp
./inotify tmp &
echo > tmp/1
echo > tmp/2
rm tmp/1 tmp/2
```

```shell
gcc -o epoll epoll.c
mkdir tmp
mkfifo tmp/1 tmp/2 tmp/3
./epoll tmp/1 tmp/2 tmp/3 &
echo aaa > tmp/1
echo bbb > tmp/2
```

```shell
gcc -o inotify_epoll inotify_epoll.c
mkdir tmp
./inotify_epoll tmp/ &
mkfifo tmp/1 tmp/2 tmp/3
echo aaa > tmp/1
echo bbb > tmp/2
rm tmp/3
```
