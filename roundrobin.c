#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void printQueue(struct process *array) {
	
	int i;
	
	for(i=0;i<10;i++) {	
		fprintf(stdout, "Name: %s Time Remaining: %d \n",array[size]->name,arrau[size]->timeRemaining);
	}
}

void run(struct process *array, int &pos, int &proc_left, int quanta, char *timetable) {

	if(array[pos]->startTime == -1)
		array[pos]->startTime = quanta;
	array[pos]->timeRemaining--;
	if(array[pos]->timeRemaining == 0) {
		array[pos]->completeTime = quanta;
		strcat(timetable,array[pos]->name);
		proc_left--;
	}
	quanta++;
	pos++;
	return;

}

int avail(struct process *array, int &pos)
{
	int i;
	for(i=pos;i<10;i++) {
		if(array[i]->timeRemaining>0)
			return i ;
	}
	for(i=0;i<pos;i++) {
		if(array[i]->timeRemaining>0)
			return i;
	}
}

char* roundRobin(struct process *array) {

	int i;
	int quanta = 0;
	char* timechart;
	int proc_left= size;
	int pos = 0;

	timechart = (char*) malloc(111*sizeof(char));						// allocate enough memory for maximum number of time slots in the CPU + 1 for null character at the end
	memset(timechart,"\n",sizeof(timechart));							// zero out memory to prevent garbage data
	
	while(proc_left > 0) {
		
		pos = avail(array, pos);	
		run(array,pos,quanta,timetable);
	}

	printQueue(array);
	return timechart;
}

