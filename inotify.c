#include <unistd.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <string.h>
#include <errno.h>

void print_usage(const char *name)
{
	printf("Usage:\n");
	printf("%s <watch_path>\n", name);
}

int read_process_inotify_fd(int fd)
{
	int res;
    char event_buf[512];
    int event_size;
    int event_pos = 0;
    struct inotify_event *event;

	/*
	 * 从文件句柄中读出事件
	 * 如果有事件的话最少应该有一个事件
	 * 所以res >= sizeof(struct inotify_event) 表示有事件发生
	 * 否则程序会休眠在这里
	 */
	res = read(fd, event_buf, sizeof(event_buf));
	if (res < (int)sizeof(struct inotify_event))
	{
		if (errno == EINTR)
			return 0;
        printf("could not get event, %s\n", strerror(errno));
        return -1;
	}


	/* event_buf里可能会有多个事件,所以需要挨个处理 */
	while (res >= sizeof(struct inotify_event))
	{
		event = (struct inotify_event *)(event_buf + event_pos);
		if (event->len)
		{
			if(event->mask & IN_CREATE)
			{
				printf("create file: %s\n", event->name);
			}
			else {
				printf("delete file: %s\n", event->name);
			}
		}
        event_size = sizeof(struct inotify_event) + event->len;
        res -= event_size;
        event_pos += event_size;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int iNotifyFd;

	if (argc < 2)
	{
		print_usage(argv[0]);
		return -1;
	}

	/* 创建一个用于notify的句柄 */
	iNotifyFd = inotify_init();

	/* 向这个notify添加需要监控的文件 */
	inotify_add_watch(iNotifyFd, argv[1], IN_DELETE | IN_CREATE);

	/* 读出notify, 处理 */
	while (1)
	{
		read_process_inotify_fd(iNotifyFd);
	}
}
