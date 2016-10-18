#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define DATA_MAX_LEN 500

void print_usage(const char *name)
{
	printf("Usage:\n");
	printf("%s <file1> [file2] [file3]\n", name);
}

int add_to_epoll(int fd, int epollFd)
{
	int result;
    struct epoll_event eventItem;
    memset(&eventItem, 0, sizeof(eventItem));
    eventItem.events = EPOLLIN;
    eventItem.data.fd = fd;
    result = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &eventItem);
	return result;
}

int main(int argc, char *argv[])
{
	int iEpollFd;
	int i;
	int iTmpFd;
	int pollResult;
	int len;
	char buf[DATA_MAX_LEN];

    /* Maximum number of signalled FDs to handle at a time */
    static const int EPOLL_MAX_EVENTS = 16;

    /* The array of pending epoll events and the index of the next event to be handled */
    struct epoll_event mPendingEventItems[EPOLL_MAX_EVENTS];

	if (argc < 2)
	{
		print_usage(argv[0]);
		return -1;
	}

	/* 打开一个epoll的句柄 */
    iEpollFd = epoll_create(8);

	/* 把每一要监控的文件都添加到epoll */
	for (i = 1; i < argc; i++)
	{
		iTmpFd = open(argv[i], O_RDWR);
		add_to_epoll(iTmpFd, iEpollFd);
	}

	/* 等待文件有数据读或写 */
	while (1)
	{
		pollResult = epoll_wait(iEpollFd, mPendingEventItems, EPOLL_MAX_EVENTS, -1);
		for (i = 0; i < pollResult; i++)
		{
			printf("Reason: 0x%x\n", mPendingEventItems[i].events);
			len = read(mPendingEventItems[i].data.fd, buf, DATA_MAX_LEN);
			buf[len] = '\0';
			printf("get data: %s\n", buf);
		}
	}
	return 0;
}
