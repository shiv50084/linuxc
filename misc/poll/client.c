#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

int main(int argc, char *argv[])
{
	int ret;
    int sock = -1;
    const int opt = 1;
    int nb = 0;
    struct sockaddr_in dest_addr;
	int nlen;

    setvbuf(stdout, NULL, _IONBF, 0);
    fflush(stdout);

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
		printf("socket error\n");
        return -1;
    }

    /* 设置该套接字为广播类型 */
    nb = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
    if(nb == -1)
    {
		printf("set socket error...\n");
        return -1;
    }

    bzero(&dest_addr, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    dest_addr.sin_port = htons(6000);
    nlen = sizeof(dest_addr);

    while(1)
    {
        sleep(1);

        /* 从广播地址发送消息 */
        char smsg[] = {"I'm a guest"};

        ret = sendto(sock, smsg, strlen(smsg), 0, (struct sockaddr*)&dest_addr, nlen);
        if(ret<0)
			printf("send error....\n");
        else
            printf("ok \n");
    }

    return 0;
}
