#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "fcfs.c"
#include "roundrobin.c"
#include "sjf.c"

#define NUM_PROCESS 15

void print_process(struct process);
void sort_process(struct process *);

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

	printf("%s\n", schedule(process_list[0], NUM_PROCESS));
	printf("%i\n", process_list[0][0].startTime);
	printf("%i\n", process_list[0][0].completeTime);
	printf("%i\n", process_list[0][0].runTime);


	printf("Start Round Robin Test\n");
	//process_list[1][0].arrivalTime = 0;	// TEST cases
	//process_list[1][0].runTimeRemaining = 2;
	//process_list[1][1].arrivalTime = 2;	// TEST cases
	//process_list[1][1].runTimeRemaining = 2;
	roundRobinTable = roundRobin(process_list[1]);
	printf("%s \n",roundRobinTable);
		

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

