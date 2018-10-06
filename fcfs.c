/* 
 * fcfs.c
 * This file implements the First-Come First-Serve (FCFS) scheduling algorithm.
 * Written for COEN 383 | Fall 2018
 */
#include <string.h>
#include <stdio.h>

#include "process.c"

// Create a structure for each process.
struct Process {
	char name;
	int arrivalTime;
	int runTime;
	int priority;
	int startTime;
	int completeTime;
	int runTimeRemaining;
};


/*
 * schedule(struct Process *, int)
 * This function will run the FCFS scheduling algorithm on the input queue.
 * Preconditions:
 *  process_list: A list of that contains Processes in the order of their arrival.
 *  size: The size of the process_list that is being inputted.
 *
 * Postconditions:
 *  process_list: The startTime, completeTime, and runTimeRemaining fields for
 *   each process will be updated with what has run.
 *  return: A string will be returned that shows when each process has run. 
 *   If a process did not run then it will contain a '-' instead.
 */
char * schedule(struct process * process_list, int size) {
	// Set the location in the 'queue' to the head.
	int loc = 0;
	// Initialize the output string.
	char output[101];

	// Initialize the current process with a remaining run time of zero.
	struct process curProcess;
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

	// Ensure that the string is properly terminated.
	output[100] = '\0';

	// Return the string.
	return strdup(&output[0]);
}
