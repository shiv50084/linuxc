#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <netdb.h>
#include <arpa/inet.h>

#if 0
struct hostent {
   char  *h_name;            /* official name of host */
   char **h_aliases;         /* alias list */
   int    h_addrtype;        /* host address type */
   int    h_length;          /* length of address */
   char **h_addr_list;       /* list of addresses */
}
#define h_addr h_addr_list[0] /* for backward compatibility */
#endif

void printout_addr(struct hostent *h)
{
	char ip[16];
	int i;

	printf("hostname : %s\n", h->h_name);
	printf("addresstype : %s\n", h->h_addrtype == AF_INET ? "IPV4" : "IPV6");
	memset(ip, 0 , sizeof(ip));
	inet_ntop(h->h_addrtype,
			h->h_addr_list[0], ip, sizeof(ip));
	printf("ip address : %s\n", ip);

	for (i = 0; h->h_aliases[i]; i++)
		printf("aliase: %s\n", h->h_aliases[i]);
}

/*
 * Usage:
 * this program will parse the "/etc/hosts"
 * add a test context as below
 *
 * # for zeroway test Start
 * 1.2.3.5 test testA www.test.org
 * # for zeroway test  End
 *
 * ./gethostent "test"
 * ./gethostent "testA"
 * ./gethostent "www.test.org"
 */
int main(int argc, char *argv[])
{
	struct hostent *h;
	int i;

	if (argc != 2)
	{
		printf("Usage : %s host\n", argv[0]);
		printf("%s \"www.test.org\"\n", argv[0]);
		exit(1);
	}

	/* parse the whole /etc/hosts file */
	while ((h = gethostent()) != NULL)
	{
		if (!strcmp(h->h_name, argv[1]))
		{
			printout_addr(h);
			exit(0);
		}
		else
		{
			for (i = 0; h->h_aliases[i]; i++)
			{
				if (!strcmp(argv[1], h->h_aliases[i]))
				{
					printout_addr(h);
					exit(0);
				}
			}
		}
	}

	endhostent();

	return 0;
}
