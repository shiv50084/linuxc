#include <unistd.h>
#include <stdlib.h>

/*
 * 由于exec函数只有错误返回值,只要返回了一定是出错了,所以不需要判断它的返回值
 */
int main(void)
{
	execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
	perror("exec ps");
	exit(1);
}

