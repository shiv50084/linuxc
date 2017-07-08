# 系统调用I/O

![IO](./IO.png)

open,read,write,close等系统函数称为无缓冲I/O(Unbuffered I/O)函数

如何选用C库函数和系统调用

- 用Unbuffered I/O函数每次读写都要进内核
- 用C标准I/O库函数要时刻注意I/O缓冲区和实际文件有可能不一致,在必要时需调用fflush
- 网络设备和终端设备读写选用Unbuffered I/O函数
