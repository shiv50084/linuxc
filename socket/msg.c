#include "msg.h"

static char msg_checksum(Msg *message)
{
	int i;
	char s = 0;

	/* simply add all message include head */
	for (i = 0 ; i < sizeof(message->head); i++)
		s += message->head[i];

	for (i = 0; i < sizeof(message->buff); i++)
		s += message->buff[i];

	return s;
}

int write_msg(int sockfd, char *buff, size_t len)
{
	Msg message;

	/* setup the message */
	memset(&message, 0 , sizeof(Msg));
	strcpy(message.head, HEAD_TAG);
	memcpy(message.buff, buff, len);
	message.checksum = msg_checksum(&message);

	/* send message, error when send len not equal */
	if (write(sockfd, &message, sizeof(Msg)) != sizeof(Msg))
		return -1;

	return sizeof(Msg);
}

int read_msg(int sockfd, char *buff, size_t len)
{
	Msg message;
	char s = 0;
	size_t size;

	memset(&message, 0, sizeof(Msg));

	/* read data from socket */
	if ((size = read(sockfd, &message, sizeof(Msg))) < 0)
	{
		/* read error */
		return -1;
	}
	else if (size == 0)
	{
		/* read to the end */
		return 0;
	}

	/* data intergrity check */
	s = msg_checksum(&message);
	if ((s == message.checksum) && (!strcmp(HEAD_TAG, message.head)))
	{
		memcpy(buff, message.buff, len);
		return sizeof(Msg);
	}

	/* error */
	return -1;
}
