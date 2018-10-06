#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.c>

char * sjf(struct process *processes) {
	
	int i;
    	for (i=0; i<10;i++){
	    printf("%c, %d, %d\n", processes[i].name, processes[i].arrivalTime, processes[i].runTime);
	}

	char quantum[120];
	int p_index = 0;
	int time, runTimeToken, tempIndex;
	
	// run the algorithm
	for (time=0; time<100;time++) {
		if (processes[p_index].runTimeRemaining != 0 && time>=processes[p_index].arrivalTime){  // check if process is still running
		    printf("%c\n", processes[p_index].name);		// debug to see character
			quantum[time] = processes[p_index].name;;	// if so, label time with process name
			processes[p_index].runTimeRemaining--;		// decrement the running time
		}
		else {
			tempIndex = p_index;				// store p_index in a temp
			runTimeToken = 11;				// reset runTimeToken
			if (processes[p_index].completeTime == 0) 	// if not already added, add the completed time for the previous process
				processes[p_index].completeTime = time;
			for (i=0;i<10;i++) {
				if (processes[i].arrivalTime <= time && i!=tempIndex && processes[i].runTime < runTimeToken && processes[i].completeTime == 0) { // lots of conditions
					p_index = i; 			// update the index to the next processes
					runTimeToken = processes[p_index].runTime;  // update the runTimeToken
				} 
			}

			if (tempIndex == p_index) {			// if p_index didn't change (no processes arrived in time), reset previous processes
				quantum[time] = '-';
			}
			else {
				quantum[time] = processes[p_index].name;	// label time with new process name
				processes[p_index].startTime = time;		// add the start time for new process
				processes[p_index].runTimeRemaining--;		// decrement run time remaining for new process
			}
		}
		printf("%d, %d, %c, %d\n", time, processes[p_index].runTimeRemaining, quantum[i], p_index); // check the state of every quantum
	}
	
	return strdup(&processes[0]);

};
