CC	= gcc

all:	schedule

schedule:	main.c roundrobin.c roundrobin.h fcfs.c
	$(CC) -o main.c roundrobin.c fcfs.c


clean:;	rm -f schedule
