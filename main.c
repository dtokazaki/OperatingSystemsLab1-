#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "fcfs.c"
#include "roundrobin.c"
#include "sjf.c"


#define NUM_PROCESS 15

void print_process(struct process);
void sort_process(struct process *);
void reset_process(struct process *);

int main() {
	// Create a 2D array of processes. Each row contains ten processses for each execution.
	struct process process_list[5][NUM_PROCESS];

	char *roundRobinTable = (char*)malloc(111*sizeof(char));

	// Fill the process list with random processes.
	int i, j, arrivalTime, runTime, priority;
	struct process insert;
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
	for(i = 0; i < 5; ++i) {
		sort_process(process_list[i]);
	}

	// Name the processes.	
	for(i = 0; i < 5; ++i) {
		for(j = 0; j < NUM_PROCESS; ++j) {
			process_list[i][j].name = (char)(65 + j);
		}
	}

	// FCFS Test.
	printf("\n == Starting First-Come First-Serve Test == \n\n");
	for(i = 0; i < 5; ++i) {
		printf("Test %i:\n", i + 1);
		printf("%s\n", schedule(process_list[i], NUM_PROCESS));
		printf("Calculate values here\n\n");
		reset_process(process_list[i]);
	}

	// RR test
	printf("\n == Starting Round Robin Test == \n\n");
	roundRobinTable = roundRobin(process_list[1]);
	printf("%s \n",roundRobinTable);

	// SJF test
	printf("\n == Starting Shortest Job First Test == \n\n");
	printf("%s\n", sjf(process_list[2]));

	// SRJF test
	printf("\n == Starting Shortest Remaining Job First Test == \n\n");
	

	// HPF (non-preemtive) test
	printf("\n == Starting Highest Priority First (non-preemptive) Test == \n\n");


	// HPF (preemptive) test
	printf("\n == Starting Highest Priority First (preemtive) Test == \n\n");


	return 0;
}

void print_process(struct process process) {
	printf("Name: %c\nArrival Time: %i\nRun Time: %i\nPriority: %i\n", process.name, process.arrivalTime, process.runTime, process.priority);
}

void sort_process(struct process * process_list) {
	int i, j;
	struct process temp;
	for(i = 0; i < NUM_PROCESS; ++i) {
		for(j = 0; j < (NUM_PROCESS - i - 1); ++j) {
			if(process_list[j].arrivalTime > process_list[j+1].arrivalTime) {
				temp = process_list[j];
				process_list[j] = process_list[j+1];
				process_list[j+1] = temp;
			}
		}
	}
}

void reset_process(struct process * process_list) {
	int i;
	for(i = 0; i < NUM_PROCESS; ++i) {
		process_list[i].startTime = -1;
		process_list[i].completeTime = -1;
		process_list[i].runTimeRemaining = process_list[i].runTime;
	}
}

