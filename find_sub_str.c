#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	/* 在字符串中查找子串 */
	const char *param = "this_is_the_head_info_will_be_fill_out_mtdparts=rk29xxnand:0x00002000@0x00002000(uboot),0x00002000@0x00004000(misc),0x00008000@0x00006000(resource),0x00008000@0x0000e000(kernel),0x00010000@0x00016000(boot),0x00010000@0x00026000(recovery),0x0001a000@0x00036000(backup),0x00040000@0x00050000(cache),0x00002000@0x00090000(kpanic),0x00180000@0x00092000(system),0x00002000@0x00212000(metadata),0x00200000@0x00214000(userdata),0x00020000@0x00414000(radical_update),-@0x00434000(user)";
	const char *mtdparts = strstr(param, "mtdparts=");
	if (!mtdparts) {
		printf("Error: 'mtdparts' not found in command line.\n");
	}
	printf("partitions :\n");
	printf("%s\n", mtdparts);

	return 0;
}


