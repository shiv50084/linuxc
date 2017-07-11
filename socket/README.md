# TCP 编程的C/S架构

![tcp_cs](./tcp_cs.png)

由于客户端不需要固定的端口,因此不必调用bind,客户端的端口号由内核自动分配

注意:
- 客户端不是不允许调用bind,只是没有必要调用bind固定一个端口号
- 服务器也不是必须调用bind,只是如果服务器不固定端口号,不方便客户端连接

实验:

在客户端connect()代码之后插入一个while(1);死循环,使客户端和服务器都处于连接状态,用netstat查看

服务器IP(192.168.1.224)
	$ ./server &
	$ netstat -apn | grep 8000
	tcp        0      0 0.0.0.0:8000            0.0.0.0:*               LISTEN      3742/server
	tcp        0      0 192.168.1.224:8000      192.168.1.100:59525     ESTABLISHED 3742/server

客户端IP(192.168.1.100)
	$ ./client abcd &
	$ netstat -apn | grep 8000
	tcp        0      0 0.0.0.0:8000            0.0.0.0:*               LISTEN      6466/./server
	tcp        0      0 192.168.1.100:59525     192.168.1.224:8000      ESTABLISHED 8092/./client

应用程序中的一个socket文件描述符对应一个socket pair,也就是源地址:源端口号和目的地址:目的端口号,也对应一个TCP连接

|socket文件描述符|源地址:源端口号|目的地址:目的端口号|状态|
|--|--|--|--|--
|server中的listen_fd|0.0.0.0:8000|0.0.0.0:\*|LISTEN|
|server中的connect_fd|192.168.1.224:8000|192.168.1.100:59525|ESTABLISHED|
|client中的sock_fd|192.168.1.100:59525|192.168.1.224:8000|ESTABLISHED|
