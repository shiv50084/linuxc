#include <stdio.h>

int main(int argc, char *argv[])
{
	/*
	 * Usage :
	 * gcc process_id.c -o process_id
	 *
	 * -rwxr-xr-x 1 zeroway users 8288 May  4 22:34 process_id*
	 * ./process_id
	 *
	 * id [user_name]
	 *
	 * 1. change owner and group owner
	 * sudo chown root.root process_id
	 * -rwsr-xr-x 1 root root 8288 May  4 22:34 process_id*
	 *
	 *
	 * 2. add stick bit and run the process again
	 *	and check euid(root now?)
	 * sudo chmod u+s process_id
	 * ./process_id
	 *
	 * id [user_name]
	 */
	printf("pid: %d\n", getpid());
	printf("ppid: %d\n", getppid());
	printf("uid: %d\n", getuid());
	printf("euid: %d\n", geteuid());
	printf("user gid: %d\n", getgid());
	printf("group gid: %d\n", getpgrp());
	printf("pgid: %d\n", getpgid(getpid()));
	printf("ppgid: %d\n", getpgid(getppid()));

	return 0;
}
