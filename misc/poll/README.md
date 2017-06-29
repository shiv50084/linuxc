# Poll函数

[Linux网络编程I/O复用之poll函数](http://blog.csdn.net/lianghe_work/article/details/46534029)

[Linux系统下UDP发送和接收广播消息](http://blog.csdn.net/robertkun/article/details/8475843)

服务器在接收客户端发来的消息同时还可以发送消息,目前客户端没有处理服务端发来的消息

测试

	gcc udp_poll_server.c -oserver
	gcc client.c -oclient

	./server
	./client
