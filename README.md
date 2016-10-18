# linuxc

## main 函数

我们知道main函数的标准原型应该是如下所示

int main(int argc, char *argv[])

argc 是命令行参数的个数

argv 是一个指向指针的指针,为什么不是指针数组呢?

因为函数原型中的[]表示指针而不表示数组,等价于 char **argv

那为什么要写成char *argv[]而不写成 char **argv 呢?

这样写给读代码的人提供了有用信息,argv 不是指向单个指针,而是指向一个指针数组的首元素

数组中每个元素都是 char *指针, 指向一个命令行参数字符串

## inotify and epoll

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
