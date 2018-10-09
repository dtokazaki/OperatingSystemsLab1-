#include "process.c"

#ifndef PRIORITYQUEUE_C
#define PRIORITYQUEUE_C
struct priorityQueue {
	struct process queue[15];
	int size;
};
#endif
