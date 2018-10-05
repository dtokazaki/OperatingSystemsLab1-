/*
 * process.c
 * The purpose of this file is to define the process structure for use in the
 * different scheduling algorithms and main,
 * Written for COEN 373 | Fall 2018
 */

// The process structure
struct process {
	// These properties are assigned before scheduling
	char name;				// The name of the process.
	int arrivalTime;		// The arrival time of the process.
	int runTime;			// The amount of time it takes to run the process.
	int priority;			// The priority of the process used by HPS.
	// These properties are updated during scheduling.
	int startTime;			// The time that the process actually started.
	int completeTime;		// The time that the process completed running.
	int runTimeRemaining;	// The amount of time left to run.
};
