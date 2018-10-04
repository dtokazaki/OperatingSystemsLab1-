/* 
 * fcfs.c
 * This file implements the First-Come First-Serve (FCFS) scheduling algorithm.
 * Written for COEN 383 | Fall 2018
 */

#include <string.h>
#include <stdio.h>

// Create a structure for each process.
typedef struct Process {
	char name;
	int arrivalTime;
	int runTime;
	int priority;
	int startTime;
	int completeTime;
	int runTimeRemaining;
} Process;

const char * schedule(struct Process * process_list, int size) {
	// Set the location in the 'queue' to the head.
	int loc = 0;
	// Initialize the output string.
	char output[120];
	// Initialize the current process.
	struct Process curProcess;
	curProcess.runTimeRemaining = 0;
	
	// Run through time.
	int time;
	for(time = 0; time < 100; ++time) {
		// If the process has completed, we need to move to the next process.
		if(process_list[loc].runTimeRemaining == 0) {
			process_list[loc].completeTime = time;
			++loc;
		}

		// We need to check that the next process is ready to run.
		if(process_list[loc].arrivalTime <= time) {
			// Check if the process has just started running.
			if(process_list[loc].runTime == process_list[loc].runTimeRemaining) {
				process_list[loc].startTime = time;
			}

			// Run the process and update the output string.
			--process_list[loc].runTimeRemaining;
			output[time] = process_list[loc].name;

		// The next process is not ready to run, so we will not run anything.
		} else {
			output[time] = '-';
		}
	}

	output[100] = '\0';
	return strdup(&output[0]);
}
