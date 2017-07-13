# ELF文件

## 三种不同类型

- 可重定位的目标文件(Relocatable或Object File)
- 可执行文件(Executable)
- 共享库(Shared Object或Shared Library)

## ELF格式提供两种不同的视角

- 链接器把ELF文件看成是Section的集合
- 加载器把ELF文件看成是Segment的集合

![elf_format](./elf_format.png)
