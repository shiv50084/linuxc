#include <stdio.h>
#include <string.h>

#define PROC_INFO_SIZE 1000000

float get_cpu_clock_speed()
{
	FILE* fp;
	char buffer[PROC_INFO_SIZE];
	size_t bytes_read;
	char* match;
	float clock_speed = -1;

	/* Read the entire contents of /proc/cpuinfo into the buffer.  */
	fp = fopen("/proc/cpuinfo", "r");
	bytes_read = fread(buffer, 1, sizeof (buffer), fp);
	/* Bail if read failed or if buffer isn't big enough */
	if (bytes_read == 0 || bytes_read == sizeof (buffer))
	{
		perror("read error or buffer not big enough\n");
		return -1;
	}
	/* NULL-terminate the text */
	buffer[bytes_read] = '\0';

	/* Locate the line that starts with "cpu MHz" */
	match = strstr(buffer, "cpu MHz");
	if (match == NULL)
	{
		perror("match is null\n");
		return -2;
	}

	/* Parse the line to extrace the clock speed.  */
	sscanf(match, "cpu MHz : %f", &clock_speed);

	fclose (fp);

	return clock_speed;
}

int main (int argc, char *argv[])
{
	printf("CPU clock speed: %4.0f MHz\n", get_cpu_clock_speed());
	return 0;
}
