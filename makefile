CC	= gcc

all:	lab1

lab1:	main.c roundrobin.c roundrobin.h fcfs.c process.c sjf.c srt.c nonpreemptivehpf.c preemptivehpf.c 
	$(CC) -o lab1 main.c


clean:;	rm -f lab1
