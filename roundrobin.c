/* 
* This file implements the Round Robin scheduling algorithm
*  
*  COEN 383 Advanced Operating Systems
*  Fall Quarter 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "fcfs.c"
#include "roundrobin.h"


void printQueue(struct Process *array, int size) {
	
	int i;
	
	for(i=0;i<size;i++) {	
		fprintf(stdout, "Name: %s Time Remaining: %d \n",array[i]->name,array[i]->runTimeRemaining);
	}
}

void run(struct Process *array, int &pos, int &proc_left, int &quanta, char *timetable) {	// main function that runs the simulation

	if(array[pos]->startTime == -1)								// startTime initialized to -1, which means it has not been updated
		if(quanta > 99) {								// Don't start any new processes after 99 quantums
			pos++;
			return;
		}
		array[pos]->startTime = quanta;
	array[pos]->runTimeRemaining--;								// decrement time remaining
	if(array[pos]->runTimeRemaining == 0) {							// if the job is done, set the completeTime, append the name to the finished string, and decrement the amount of processes left
		array[pos]->completeTime = quanta;
		strcat(timetable,array[pos]->name);
		proc_left--;
	}
	quanta++;										// increase the quanta
	pos++;
	if(pos == 10)										// if the pos reaches the end of the array, start over from the begining
		pos = 0;
	return;

}

int avail(struct Process *array, int &pos, int quanta, int size)						// Test to see if a process is available
{
	int i;
	for(i=pos;i<size;i++) {
		if(array[i]->runTimeRemaining>0 && array[i]->arrivalTime <= quanta)		// Process must be still running, and have arrived before the current quanta
			return i;
	}
	for(i=0;i<pos;i++) {
		if(array[i]->runTimeRemaining>0 array[i]->arrivalTime <= quanta)
			return i;
	}
	return -1;
}

char* roundRobin(struct Process *array) {

	int i;
	int quanta = 0;
	char* timechart;
	int proc_left= size;
	int pos = 0;
	char error[2] = "*";
	int size = 15;														// Total amoutn of processes

	timechart = (char*) malloc(111*sizeof(char));						// allocate enough memory for maximum number of time slots in the CPU + 1 for null character at the end
	memset(timechart,"\0",sizeof(timechart));						// zero out memory to prevent garbage data
	
	while(proc_left > 0) {									// Exit lop when no more processes left
		
		pos = avail(array, pos, quanta, size);
		if(pos == -1) {									// If no process is available, CPU is idle, and advance the quanta
			quanta++;
			strcat(timetable,error);
		}
		else	
			run(array,pos,proc_left,quanta,timetable);					// Only run if there is a process available, and has arrived						
	}

	printQueue(array);									// Print function for debugging purposes
	return timechart;
}

