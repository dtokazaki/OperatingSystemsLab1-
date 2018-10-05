CC	= gcc

all:	lab1

lab1:	main.c roundrobin.c roundrobin.h fcfs.c
	$(CC) -o lab1 main.c fcfs.c roundrobin.c


clean:;	rm -f lab1
