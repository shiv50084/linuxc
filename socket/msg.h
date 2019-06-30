#ifndef __MSG_H__
#define __MSG_H__
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define HEAD_INFO 10
#define BUFFER_LEN 1024
#define HEAD_TAG "lnxmsg"

typedef struct {
	/* head info */
	char head[HEAD_INFO];

	/* check sum */
	char checksum;

	/* buffer for real data */
	char buff[BUFFER_LEN];
}Msg;

extern int write_msg(int sockfd, char *buff, size_t len);
extern int read_msg(int sockfd, char *buff, size_t len);

#endif
