#include <stdio.h>

/*
 * 求结构体成员偏移量
 */
#define __OFFSET(type, member) (&((type *)(0))->member)

/*
 * 求结构体首地址
 * 成员变量的地址减去该成员在结构体中的偏移量就是结构体首地址
 * 这个宏的目的就是返回(type*)类型的指针
 */
#define my_container_of(ptr, type, member)	\
	(type *)( (unsigned char *)(ptr) - (size_t)&( ((type *)(0))->member) )

struct test {
	int a;
	int b;
	int c;
	char d;
};

int main(int argc, char **argv)
{
	struct test t;
	printf("test = %p\n", &t);
	printf("test.c = %p\n", &(t.c));

	/*
	 * 把结构体test的一个实例映射到0这个地址
	 * 这样成员的地址就是在0的基础上往上加
	 * 进而此时成员的地址
	 */
	printf("offset of struct->c= %p\n", &(((struct test *)(0))->c));

	printf("offset of c= %p\n", __OFFSET(struct test, c));
	printf("offset of d= %p\n", __OFFSET(struct test, d));

	/*
	 * 求结构体首地址
	 * 成员变量的地址减去该成员在结构体中的偏移量就是结构体首地址
	 *
	 * 指针的加减操作的步长是按照这个指针的类型来定的
	 * 所以这里需要把指向成员变量c的指针类型改为char
	 */
	printf("struct test address is %p\n", (unsigned char *)&(t.c) - (size_t)&(((struct test *)(0))->c));
	printf("struct test address is %p\n", (unsigned char *)&(t.d) - (size_t)&(((struct test *)(0))->d));
	printf("struct test address is %p\n", my_container_of(&t.c, struct test, c));
	printf("struct test address is %p\n", my_container_of(&t.d, struct test, d));

	return 0;
}
