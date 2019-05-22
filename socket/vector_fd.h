#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
	int *fd;
	int counter;
	int max_counter;
}VectorFD;

extern VectorFD* create_vector_fd(void);
extern void destory_vector_fd(VectorFD *vfd);
extern int get_fd(VectorFD *vfd, int index);
extern void remove_fd(VectorFD *vfd, int fd);
extern void add_fd(VectorFD *vfd, int fd);

#endif
