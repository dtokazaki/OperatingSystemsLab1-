#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "fcfs.c"
#include "roundrobin.c"
#include "roundrobin.h"

#define NUM_PROCESS 15

void print_process(struct Process);

int main() {
	// Create a 2D array of processes. Each row contains ten processses for each execution.
	struct Process process_list[5][NUM_PROCESS];
	
	// Fill the process list with random processes.
	int i, j, arrivalTime, runTime, priority;
	struct Process insert;
	srand(time(NULL));
	for(i = 0; i < 5; ++i) {
		for(j = 0; j < NUM_PROCESS; ++j) {
			arrivalTime = rand() % 100;
			runTime = (rand() % 10) + 1;
			priority = (rand() % 4) + 1;

			process_list[i][j].name = ' ';
			process_list[i][j].arrivalTime = arrivalTime;
			process_list[i][j].runTime = runTime;
			process_list[i][j].priority = priority;
			process_list[i][j].startTime = -1;
			process_list[i][j].completeTime = -1;
			process_list[i][j].runTimeRemaining = runTime;
		}
	}

	// Sort the processes.
	int k;
	struct Process temp;
	for(i = 0; i < 5; ++i) {
		for(j = 0; j < NUM_PROCESS; ++j) {
			for(k = 0; k < (NUM_PROCESS - j - 1); ++k) {
				if(process_list[i][k].arrivalTime > process_list[i][k+1].arrivalTime) {
					temp = process_list[i][k];
					process_list[i][k] = process_list[i][k+1];
					process_list[i][k+1] = temp;
				}
			}
		}
	}

	// Name the processes.	
	for(i = 0; i < 5; ++i) {
		for(j = 0; j < NUM_PROCESS; ++j) {
			process_list[i][j].name = (char)(65 + j);
		}
	}

	printf("%s\n", schedule(process_list[0], NUM_PROCESS));
	printf("%i\n", process_list[0][0].startTime);
	printf("%i\n", process_list[0][0].completeTime);
	printf("%i\n", process_list[0][0].runTime);

	

	return 0;
}

void print_process(struct Process process) {
	printf("Name: %c\nArrival Time: %i\nRun Time: %i\nPriority: %i\n", process.name, process.arrivalTime, process.runTime, process.priority);
}
