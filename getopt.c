#include <stdio.h>
#include <unistd.h>

/*
 * optind is the index of the next element to be processed in argv
 */

/*
 * Usage:
 * optstring a:bc:d::e
 * -b -e 不接参数(右边没有分隔符)
 * -d 可接,也可以不接,参数不保存存在optarg中(左右两边都有分隔符)
 * -a -c 必须要接参数,参数保存在optarg中(右边有分隔符)
 *
 * 比较下面三个结果知道可选参数-d和不接参数-b,-e的区别
 *  ./a.out -bed
 *  ./a.out -dbe be作为里-d的参数
 *  ./a.out -deb be作为里-d的参数
 */
int main(int argc, char *argv[])
{
	int opt;
	const char *optstring = "a:bc:d::e";
	printf("%s\n", optstring);

	while ((opt = getopt(argc, argv, optstring)) != -1)
	{
		printf("opt = %c, optarg = %s, optind = %d, argv[%d] = %s\n", opt, optarg, optind, optind, argv[optind]);
	}
	return 0;
}
