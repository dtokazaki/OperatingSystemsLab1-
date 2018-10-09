#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "fcfs.c"
#include "roundrobin.c"
#include "sjf.c"

// TODO Add srt.c and hpf.c

#define NUM_PROCESS 10

struct average {
	double turnaround;
	double waiting;
	double response;
	int throughput;
};

void print_process(struct process *);
void sort_process(struct process *);
void reset_process(struct process *);
void reset_average(struct average);
struct average averages(struct process *);
void print_average(struct average);
void print_comb_average(struct average);

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
			runTime = (rand() % 10) + 6;
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

	struct average averageReturns;
	struct average averageCombined = {0, 0, 0};

	printf("Press enter to go through each set of tests\n");
	getchar();

	printf("Processes\n");
	for(i = 0; i < 5; ++i) {
		printf(" Test Set %i\n", i + 1);
		print_process(process_list[i]);
		printf("\n");
	}

	// Wait for user input
	getchar();

	// FCFS Test
	printf("\n== Starting First-Come First-Serve Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", fcfs(process_list[i], NUM_PROCESS));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for FCFS.
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	getchar();

	// RR Test
	printf("== Starting Round Robin Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", roundRobin(process_list[i]));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for RR.
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	getchar();

	// SJF Test
	printf("== Starting Shortest Job First Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", sjf(process_list[i]));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for SJF.
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	getchar();	

	// SRJF Test
	printf("== Starting Shortest Remaining Job First Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		// TODO SRJF
		printf("  NOT COMPLETED YET\n");
		// printf("  %s\n", srt(process_list[i]));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for SRJF.
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	getchar();

	// HPF (non-preemtive) Test
	printf("== Starting Highest Priority First (non-preemptive) Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		// TODO HPF (NP)
		printf("  NOT COMPLETED YET\n");
		// printf("  %s\n", roundRobin(process_list[i]));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for HPF (non-preemptive)..
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	getchar();
	
	// HPF (preemptive) Test
	printf("== Starting Highest Priority First (preemptive) Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		// TODO HPF (P)_
		printf("  NOT COMPLETED YET\n");
		// printf("  %s\n", roundRobin(process_list[i]));
		
		// Get the average values, print, and add them to algorithm wide average.
		averageReturns = averages(process_list[i]);
		print_average(averageReturns);
		averageCombined.turnaround += averageReturns.turnaround;
		averageCombined.waiting += averageReturns.waiting;
		averageCombined.response += averageReturns.response;

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for HPF (preemptive).
	printf(" Total:\n");
	print_comb_average(averageCombined);
	reset_average(averageCombined);

	return 0;
}

void print_process(struct process * process_list) {
	int i;
	for(i = 0; i < NUM_PROCESS; ++i) {
		printf("  Name: %c | Arrival Time: %02i | Run Time: %02i | Priority: %02i\n", 
			process_list[i].name,
			process_list[i].arrivalTime,
			process_list[i].runTime,
			process_list[i].priority);
	}
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

void reset_average(struct average averages) {
	averages.turnaround = 0;
	averages.waiting = 0;
	averages.response = 0;
}

struct average averages(struct process * process_list) {
	int numStarted;
	int numCompleted;
	int i;
	double response = 0;
	double waiting = 0;
	double turnaround = 0;
	for(i = 0; i < NUM_PROCESS; ++i) {
		// Check that the process has started.
		if(process_list[i].startTime != -1) {
			response += process_list[i].startTime - process_list[i].arrivalTime;
			++numStarted;
		}
		// Check that the process has completed.
		if(process_list[i].completeTime != -1) {
			waiting += (process_list[i].completeTime - process_list[i].arrivalTime) - process_list[i].runTime;
			turnaround += (process_list[i].completeTime - process_list[i].arrivalTime);
			++numCompleted;
		}
	}

	struct average aveReturn;
	aveReturn.response = response / NUM_PROCESS;
	aveReturn.waiting = waiting / NUM_PROCESS;
	aveReturn.turnaround = turnaround / NUM_PROCESS;

	return aveReturn;
}

void print_average(struct average averages) {
	printf("  Avg. Turnaround Time: %.2f\n  Avg. Waiting Time:    %.2f\n  Avg. Response Time:   %.2f\n\n",
		averages.turnaround, averages.waiting, averages.response);
}

void print_comb_average(struct average averages) {
	averages.turnaround = averages.turnaround / 5;
	averages.waiting = averages.waiting / 5;
	averages.response = averages.response / 5;
	print_average(averages);
}
