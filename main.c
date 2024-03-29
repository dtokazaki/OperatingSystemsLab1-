#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "fcfs.c"
#include "roundrobin.c"
#include "sjf.c"
#include "srt.c"
#include "nonpreemptivehpf.c"
#include "preemptivehpf.c"

#define NUM_PROCESS 10

// Create a struct to deal with averages of statistics
struct average {
	double turnaround;
	double waiting;
	double response;
	int throughput;
};

// Create a special struct for the HPF averages.
struct hpfAverage {
	struct average averages[5];
};

void print_process(struct process *);
void sort_process(struct process *);
void reset_process(struct process *);
void reset_average(struct average *);
struct average averages(struct process *);
void print_average(struct average);
void print_comb_average(struct average);
struct hpfAverage hpf_averages(struct process *);
void print_hpf_average(struct hpfAverage);
void print_hpf_comb_average(struct hpfAverage, int, int); 
void reset_hpf_average(struct hpfAverage *); 

int main() {
	// Create a 2D array of processes. Each row contains ten processses for each execution.
	struct process process_list[5][NUM_PROCESS];

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

	// Create the structs that will add up the averages.
	struct average averageReturns;
	struct average averageCombined = {0, 0, 0};

	printf("Press enter to go through each set of tests\n");
	getchar();

	// Print out all of the processes for reference.
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
	reset_average(&averageCombined);

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
	reset_average(&averageCombined);

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
	reset_average(&averageCombined);

	getchar();	

	// SRJF Test
	printf("== Starting Shortest Remaining Job First Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", srt(process_list[i]));
		
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
	reset_average(&averageCombined);

	getchar();

	// Create the special structs for the HPF runs.
	struct hpfAverage hpfAverageReturns;
	struct hpfAverage hpfAverageCombined;
	reset_hpf_average(&hpfAverageCombined);

	int numStart, numComplete;

	// HPF (non-preemtive) Test
	printf("== Starting Highest Priority First (non-preemptive) Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", nonpreemptivehpf(process_list[i], NUM_PROCESS));
		
		// Get the average values, print, and add them to algorithm wide average.
		hpfAverageReturns = hpf_averages(process_list[i]);
		print_hpf_average(hpfAverageReturns);
		
		numStart = 0;
		numComplete = 0;
		for(j = 0; j < 5; ++j) {
			if(hpfAverageReturns.averages[j].turnaround != 0)
				numComplete++;
			if(hpfAverageReturns.averages[j].response != 0)
				numStart++;
			hpfAverageCombined.averages[j].turnaround += hpfAverageReturns.averages[j].turnaround;
			hpfAverageCombined.averages[j].waiting += hpfAverageReturns.averages[j].waiting;
			hpfAverageCombined.averages[j].response += hpfAverageReturns.averages[j].response;
		}

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for HPF (non-preemptive)..
	printf(" Total:\n");
	print_hpf_comb_average(hpfAverageCombined, numStart, numComplete);
	reset_hpf_average(&hpfAverageCombined);

	getchar();
	
	// HPF (preemptive) Test
	printf("== Starting Highest Priority First (preemptive) Test ==\n");
	for(i = 0; i < 5; ++i) {
		// Print test number and the process order.
		printf(" Test %i:\n", i + 1);
		printf("  %s\n", preemptivehpf(process_list[i], NUM_PROCESS));
		
		// Get the average values, print, and add them to algorithm wide average.
		hpfAverageReturns = hpf_averages(process_list[i]);
		print_hpf_average(hpfAverageReturns);
		
		numStart = 0;
		numComplete = 0;
		for(j = 0; j < 5; ++j) {
			if(hpfAverageReturns.averages[j].turnaround != 0)
				numComplete++;
			if(hpfAverageReturns.averages[j].response != 0)
				numStart++;
			hpfAverageCombined.averages[j].turnaround += hpfAverageReturns.averages[j].turnaround;
			hpfAverageCombined.averages[j].waiting += hpfAverageReturns.averages[j].waiting;
			hpfAverageCombined.averages[j].response += hpfAverageReturns.averages[j].response;
		}

		// Reset the process list for the next algorithm.
		reset_process(process_list[i]);
	}
	// Print the total averages for HPF (preemptive).
	printf(" Total:\n");
	print_hpf_comb_average(hpfAverageCombined, numStart, numComplete);
	reset_hpf_average(&hpfAverageCombined);

	return 0;
}

void print_process(struct process * process_list) {
	// Helper function to easily print out process information.
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
	// Quick bubble sort function to ensure that the processes are sorted by arrival time.
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
	// This will reset the mutable process properties between algorithms that are needed for testing.
	int i;
	for(i = 0; i < NUM_PROCESS; ++i) {
		process_list[i].startTime = -1;
		process_list[i].completeTime = -1;
		process_list[i].runTimeRemaining = process_list[i].runTime;
	}
}

void reset_average(struct average * averages) {
	// This resets the average between algorithms.
	(*averages).turnaround = 0;
	(*averages).waiting = 0;
	(*averages).response = 0;
}

struct average averages(struct process * process_list) {
	// This will average the process statistics.
	// The number of processes that have been run or started.
	int numStarted = 0;
	int numCompleted = 0;
	int i;

	// The aggregation of the different parameters. 
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
	aveReturn.response = response / numStarted;
	aveReturn.waiting = waiting / numCompleted;
	aveReturn.turnaround = turnaround / numCompleted;

	return aveReturn;
}

void print_average(struct average averages) {
	// Print the averages that are calculated.
	printf("  Avg. Turnaround Time: %.2f\n  Avg. Waiting Time:    %.2f\n  Avg. Response Time:   %.2f\n\n",
		averages.turnaround, averages.waiting, averages.response);
}

void print_comb_average(struct average averages) {
	// Print the combined averages from five runs.
	averages.turnaround = averages.turnaround / 5;
	averages.waiting = averages.waiting / 5;
	averages.response = averages.response / 5;
	print_average(averages);
}

struct hpfAverage hpf_averages(struct process * process_list) {
	// The averages at each priority level.
	struct hpfAverage average;
	// The number of processes started and completed at each level.
	int numStart[5];
	int numComplete[5];	

	// Ensure all the initial averages are set to zero.
	int i;
	for(i = 0; i < 5; ++i) {
		average.averages[i].turnaround = 0;
		average.averages[i].waiting = 0;
		average.averages[i].response = 0;
		numStart[i] = 0;
		numComplete[i] = 0;
	}

	int waiting;
	int turnaround;

	for(i = 0; i < NUM_PROCESS; ++i) {
		// Check that the process has started.
		if(process_list[i].startTime != -1) {
			// Update global stats.
			average.averages[0].response += process_list[i].startTime - process_list[i].arrivalTime;
			++numStart[0];

			// Update level stats.
			average.averages[process_list[i].priority].response += process_list[i].startTime - process_list[i].arrivalTime;
			++numStart[process_list[i].priority];
		}
		// Check that the process has completed.
		if(process_list[i].completeTime != -1) {
			// Update global stats.
			waiting = (process_list[i].completeTime - process_list[i].arrivalTime) - process_list[i].runTime;
			turnaround = process_list[i].completeTime - process_list[i].arrivalTime;
			average.averages[0].waiting += waiting;
			average.averages[0].turnaround += turnaround;
			++numComplete[0];

			// Update level stats.
			average.averages[process_list[i].priority].waiting += waiting;
			average.averages[process_list[i].priority].turnaround += turnaround;
			++numComplete[process_list[i].priority];
		}
	}

	// Compute average based on number started and completed.
	for(i = 0; i < 5; ++i) {
		// Handle if the process queue is not run or empty.
		if(numStart[i] != 0) {
			average.averages[i].response = average.averages[i].response / numStart[i];
		} else { 
			average.averages[i].response = 0;
		}

		// Handle if the process queue is not run or empty.
		if(numComplete[i] != 0) {
			average.averages[i].waiting = average.averages[i].waiting / numComplete[i];
			average.averages[i].turnaround = average.averages[i].turnaround / numComplete[i];
		} else {
			average.averages[i].waiting = 0;
			average.averages[i].turnaround = 0;
		}
	}

	return average;
}

void print_hpf_average(struct hpfAverage average) {
	int i;
	for(i = 0; i < 5; ++i) {
		// Print the header.
		if(i == 0) {
			printf("  All Queues:\n");
		} else {
			printf("  Priority Queue %i:\n", i);
		}
		// Print the information.
		printf("   Avg. Turnaround Time: %.2f | Avg. Waiting Time: %.2f | Avg. Response Time: %.2f\n",
			average.averages[i].turnaround, average.averages[i].waiting, average.averages[i].response);
	}
}

void print_hpf_comb_average(struct hpfAverage average, int numStart, int numComplete) {
	int i;
	for(i = 0; i < 5; ++i) {
		average.averages[i].turnaround = average.averages[i].turnaround / numComplete;
		average.averages[i].waiting = average.averages[i].waiting / numComplete;
		average.averages[i].response = average.averages[i].response / numStart;
	}
	print_hpf_average(average);
}

void reset_hpf_average(struct hpfAverage * average) {
	int i;
	for(i = 0; i < 5; ++i) {
		(*average).averages[i].turnaround = 0;
		(*average).averages[i].waiting = 0;
		(*average).averages[i].response = 0;
	}
}
