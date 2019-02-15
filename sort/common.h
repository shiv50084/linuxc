#ifndef _COMMON_H_
#define _COMMON_H_

#define ARRAY_LEN(x) (sizeof(x)/sizeof((x)[0]))
void swap(int *a, int *b);
void show_array(int array[], int len);
void insert_sort_show_array(int array[], int len, int key_index);

#endif
