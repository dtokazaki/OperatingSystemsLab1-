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

#include "process.c"

#ifndef COEN383_LAB1
#define COEN383_LAB1

#define NUM_PROCESS 10
void printQueue(struct process *array, int size) {
	
	int i;
	
	for(i=0;i<size;i++) {	
		fprintf(stdout, "Name: %c Arrival Time: %d, Start Time: %d, runTime: %d, Time Remaining: %d \n",array[i].name,array[i].arrivalTime,array[i].startTime,array[i].runTime,array[i].runTimeRemaining);
	}
}

void run(struct process *array, int *pos, int *proc_left, int *quanta,int size, char *timetable) {	// main function that runs the simulation

	char *string;

	string = (char*)malloc(2*sizeof(char));
	memset(string,'\0', sizeof(string));

	if(array[*pos].startTime == -1) {
		if(*quanta <= 99) {							// startTime initialized to -1, which means it has not been updated
			array[*pos].startTime = *quanta;
		}
		else {
			(*quanta)++;
			return;
		}

	}
	array[*pos].runTimeRemaining--;		

	string[0] = array[*pos].name;
	strcat(timetable,string);

	if(array[*pos].runTimeRemaining == 0) {							// if the job is done, set the completeTime, append the name to the finished string, and decrement the amount of processes left
		array[*pos].completeTime = *quanta;
		(*proc_left)--;
	}

	(*quanta)++;	 										// increase the quanta
	(*pos)++;
	if(*pos == size)										// if the pos reaches the end of the array, start over from the begining
		*pos = 0;

}

int avail(struct process *array, int pos, int quanta, int size)						// Test to see if a process is available
{
	int i;
	for(i=pos;i<size;i++) {
		if(array[i].runTimeRemaining>0 && array[i].arrivalTime <= quanta)		// Process must be still running, and have arrived before the current quanta
			return i;
	}
	for(i=0;i<pos;i++) {
		if(array[i].runTimeRemaining>0 && array[i].arrivalTime <= quanta)
			return i;
	}
	return -1;
}

char* roundRobin(struct process *array) {

	int i;
	int quanta = 0;
	char* timechart;
	int size = NUM_PROCESS;										// Total amount of processes
	int proc_left= size;
	int pos = 0;
	int oldpos;
	char error[2] = "-";
							
	timechart = (char*) malloc(((size*10)+11)*sizeof(char));						// allocate enough memory for maximum number of time slots in the CPU + 1 for null character at the end
	memset(timechart,'\0',sizeof(timechart));						// zero out memory to prevent garbage data
	
	 while(proc_left > 0 && quanta <= ((size*10)+10)) {						// Exit loop when no more processes left
		oldpos = pos;
		pos = avail(array, pos, quanta, size);
	
		if(pos == -1) {
			quanta++;								// If no process is available, CPU is idle, and advance the quanta
			strcat(timechart,error);
			pos=oldpos;								// reset pos back to old position
		}
		else {	
			
			run(array,&pos,&proc_left,&quanta,size,timechart);			// Only run if there is a process available, and has arrived	
		}
	}
	
	// Commenting this out for now. -SP
	// printQueue(array,size);									// Print function for debugging purposes

	return timechart;
}
#endif
