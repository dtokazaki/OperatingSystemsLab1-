CC	= gcc

all:	schedule

schedule:	main.c roundrobin.c roundrobin.h fcfs.c
	$(CC) -o main.c


clean:;	rm -f schedule
