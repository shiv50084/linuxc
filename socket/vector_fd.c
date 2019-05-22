#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include "vector_fd.h"

#define ENLAGE_NR 5
#define DEFALT_FD_NR 5
#define DEFALT_VECTOR_NR 1

/* 动态创建一个保存客户端连接的容器 */
VectorFD* create_vector_fd(void)
{
	VectorFD *vfd = (VectorFD *)calloc(DEFALT_VECTOR_NR, sizeof(VectorFD));
	assert(vfd != NULL);

	vfd->fd = (int *)calloc(DEFALT_FD_NR, sizeof(int));
	assert(vfd->fd != NULL);

	vfd->counter = 0;
	vfd->max_counter = 0;

	return vfd;
}

void destory_vector_fd(VectorFD *vfd)
{
	assert(vfd != NULL);
	free(vfd->fd);
	free(vfd);
}

int get_fd(VectorFD *vfd, int index)
{
	assert(vfd != NULL);

	if (index < 0 || index > vfd->counter - 1)
		return 0;

	return vfd->fd[index];
}

static int indexof(VectorFD *vfd, int fd)
{
	int i;

	for (i = 0; i < vfd->counter; i++)
		if (vfd->fd[i] == fd)
			return i;

	return -1;
}

void remove_fd(VectorFD *vfd, int fd)
{
	int index;
	int i;

	assert(vfd != NULL);

	index = indexof(vfd, fd);
	if (index == -1)
		return;

	/* 后面的覆盖需要删除的fd即可 */
	for (i = index; i < vfd->counter - 1; i++)
		vfd->fd[i] = vfd->fd[i+1];
	vfd->counter--;
}

/* 动态扩大容器的大小 */
static void encapacity(VectorFD *vfd)
{
	int *fds;

	if (vfd->counter >= vfd->max_counter)
	{
		fds = (int *)calloc(vfd->counter + ENLAGE_NR, sizeof(int));
		assert(fds != NULL);
		memcpy(fds, vfd->fd, sizeof(int) * vfd->counter);
		free(vfd->fd);
		vfd->fd = fds;
		vfd->max_counter += ENLAGE_NR;
	}
}

/* 添加fd到容器中 */
void add_fd(VectorFD *vfd, int fd)
{
	assert(vfd != NULL);
	encapacity(vfd);
	vfd->fd[vfd->counter++] = fd;
}
