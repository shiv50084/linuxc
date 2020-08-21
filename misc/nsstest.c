#include <stdio.h>

struct testNSSData {
    const char *hostname;
    const char *const *ipAddr;
    int af;
};

static int testGetHostByName(const void *opaque)
{
	struct testNSSData *data = (struct testNSSData *)opaque;
	int i = 0;
	do
	{
		printf("%s:%s<%d>\n", data->hostname, data->ipAddr[i], data->af);
		i++;
	} while (data->ipAddr[i]);

	return 0;
}

int virTestRun(const char *name, int(*body)(const void *data), const void *data)
{
	body(data);

	return 0;
}

int main(int argc, char *argv[])
{
	int ret = 0;
# define DO_TEST(name, family, ...) \
    do { \
        const char *addr[] = { __VA_ARGS__, NULL}; \
        struct testNSSData data = { \
            .hostname = name, .ipAddr = addr, .af = family, \
        }; \
        if (virTestRun(name, testGetHostByName, &data) < 0) \
            ret = -1; \
    } while (0)

    DO_TEST("fedora", 1, "192.168.122.197", "192.168.122.198", "192.168.122.199");
    DO_TEST("gentoo", 2, "2001:1234:dead:beef::2");
    DO_TEST("pentoo", 3, "");
    DO_TEST("bentoo", 4, NULL);

	return ret;
}
