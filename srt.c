#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "process.h"

typedef enum { false, true } bool;  

char * sjf(struct process *processes) {

	char quantum[120];
	int p_index = 0;
	int time, runTimeToken, tempIndex;
	bool change;
	
	// run the algorithm
	for (time=0; time<100;time++) {
		runTimeToken = 11;
		change = false;
		tempIndex = p_index;
		for (i=0;i<10;i++) {	// find the shortest remaining time
			if (processes[i].arrivalTime <= time && processes[i].runTimeRemaining < runTimeToken && processes[i].runTimeRemaining > 0) { // lots of conditions
				p_index = i; 	/
				runTimeToken = processes[p_index].runTimeRemaining;  
				change = true;
			} 
		}
		
		if (!change) {				// if there was no change in p_index	
			if (processes[p_index].runTimeRemaining > 0 && processes[p_index].arrivalTime<=time) {	   // if same process still running
			 	if (processes[p_index].runTimeRemaining == processes[p_index].runTime)
			        	processes[p_index].startTime = time;
				quantum[time] = processes[p_index].name;		
				processes[p_index].runTimeRemaining--;
			}
			else if (processes[p_index].completeTime == 0 && processes[p_index].runTimeRemaining == 0) {  // if same process has ended
				quantum[time] = '-';	
				processes[tempIndex].completeTime = time-1;
			}
			else 	// there is no process running
				quantum[time] = '-';	
		}
		else {		// if the p_index changed						
			if (processes[tempIndex].runTimeRemaining == 0 && processes[tempIndex].completeTime == 0)	 // if previous process is complete
				processes[tempIndex].completeTime = time-1;			
			if  (processes[p_index].runTimeRemaining == processes[p_index].runTime)
				processes[p_index].startTime = time;				
			quantum[time] = processes[p_index].name;			
			printf("%c\n", processes[p_index].name);
			processes[p_index].runTimeRemaining--;				
		}
	}
	
	quantum[119] = '\0';	
	return strdup(&quantum[0]);
};
