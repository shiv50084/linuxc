all : execlp upper wrapper

execlp : exec_function.c
	gcc -o $@ $<
upper : upper.c
	gcc -o $@ $<
wrapper : wrapper.c
	gcc -o $@ $<

clean :
	rm execlp upper wrapper
