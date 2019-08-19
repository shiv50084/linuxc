# Poll函数

## 网络编程中的例子

[Linux网络编程I/O复用之poll函数](http://blog.csdn.net/lianghe_work/article/details/46534029)

[Linux系统下UDP发送和接收广播消息](http://blog.csdn.net/robertkun/article/details/8475843)

服务器在接收客户端发来的消息同时还可以发送消息,目前客户端没有处理服务端发来的消息

测试

	gcc udp_poll_server.c -oserver
	gcc client.c -oclient

	./server
	./client

## poll和select

poll系统调用优于select的几点

- poll无需使用者计算最大的文件描述符值加一和传递该参数
- poll在应对较大值的描述符更有效率
- select文件描述符集合是静态大小的(poll可以创建合适大小的数组)
- select的文件描述符集合会在返回时重新创建,所以之后每次调用都必须重新初始化

select的优点

- poll在某些unix上不支持，所以select移植性会好一点
- select提供了更好的超时方案(微秒级别)
- poll和pselect理论上提供纳秒级别精度，但实际中没有任何调用可以可靠的提供微秒级别精度

比poll和select更好的epoll
