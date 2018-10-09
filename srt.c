#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "process.h"

typedef enum { false, true } bool;  

char * sjf(struct process *processes) {

	char quantum[120]; // our timetracker of 100  time slices
	int p_index = 0; // keeps track of the current process in our process array
	int time, runTimeToken, tempIndex;
	bool change;
	
	// run the algorithm
	for (time=0; time<100;time++) {
		runTimeToken = 11;	// used to compare/change for every new runTime that is lower than the previous
		change = false;		// token to see if change occurred
		tempIndex = p_index;	// store the current process index in case we go to a new process
		for (i=0;i<10;i++) {	// find the shortest remaining time
			if (processes[i].arrivalTime <= time && processes[i].runTimeRemaining < runTimeToken && processes[i].runTimeRemaining > 0) { // lots of conditions
				p_index = i; 	// change to the new process with a shorter run time
				runTimeToken = processes[p_index].runTimeRemaining;   // update comparison runTime toekn
				change = true; // use for following statements
			} 
		}
		
		if (!change) { 		// if there was no change in p_index	
			if (processes[p_index].runTimeRemaining > 0 && processes[p_index].arrivalTime<=time) {	   // if the process is not complete
			 	if (processes[p_index].runTimeRemaining == processes[p_index].runTime)	// and if it is new,
			        	processes[p_index].startTime = time;		// then set its start time
				quantum[time] = processes[p_index].name;	// then put the process name in our quantum
				processes[p_index].runTimeRemaining--;		// and decrement the runTimeRemaining
			}
			else if (processes[p_index].completeTime == 0 && processes[p_index].runTimeRemaining == 0) {  // if process has ended
				quantum[time] = '-';	// then add a '-' to our quantum
				processes[tempIndex].completeTime = time-1; // and set its complete time
			}
			else 	// there is no process running
				quantum[time] = '-';	// just put a '-' in our quantum
		}
		else {   // if the p_index changed, aka we have a different or new process						
			if (processes[tempIndex].runTimeRemaining == 0 && processes[tempIndex].completeTime == 0)  // if previous process is complete
				processes[tempIndex].completeTime = time-1;	// then set its complete time
			if  (processes[p_index].runTimeRemaining == processes[p_index].runTime)  // if the next process is entirely new
				processes[p_index].startTime = time;	// set its start time	
			quantum[time] = processes[p_index].name;   // then put the process name in our quantum		
			processes[p_index].runTimeRemaining--;	   // and decrement the runTimeRemaining			
		}
	}
	
	quantum[119] = '\0';	
	return strdup(&quantum[0]);
};
