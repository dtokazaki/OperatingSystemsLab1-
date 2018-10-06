#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct process {
	char name;
	int arrivalTime; // 0-99
	int runTime; // 1-10
	int priority; // 1-5
	int startTime;
	int completeTime;
	int runTimeRemaining;
};

struct process processes[10];

int main() {
	
	// provide letters
	char alphabet[10] = {'A','B','C','D','E','F','G','H','I','J'};
	
	// give values to processes
	int i;
	srand(time(NULL));
	for (i=0; i<10;i++){
	    
		int run_time = 1 + rand()%10;
		processes[i].name = alphabet[i];
		processes[i].arrivalTime = rand()%100;
		processes[i].runTime = run_time;
		processes[i].priority = (1 + rand()%6);
		processes[i].startTime = 0;
		processes[i].completeTime = 0;
		processes[i].runTimeRemaining = run_time;
	};
	
	// sort the process array by arrival time
	int j;
	for (i=0;i<10;i++){
		for (j=0;j<10-i-1;j++){
			if (processes[j].arrivalTime > processes[j+1].arrivalTime){
				struct process temp = processes[j];
				processes[j] = processes[j+1];
				processes[j+1] = temp;
			}
		}
	};

    for (i=0; i<10;i++){
	    printf("%c, %d, %d\n", processes[i].name, processes[i].arrivalTime, processes[i].runTime);
	}

	char quantum[120];
	int p_index = 0;
	int time, runTimeToken, tempIndex;
	
	// run the algorithm
	for (time=0; time<100;time++) {
		runTimeToken = 11;
		tempIndex = p_index;
		for (i=0;i<10;i++) {
			if (processes[i].arrivalTime <= time && i!=tempIndex && processes[i].runTime < runTimeToken && processes[i].runTimeRemaining != 0) { // lots of conditions
				p_index = i; 								// update the index to the next processes
				runTimeToken = processes[p_index].runTime;  // update the runTimeToken
			} 
		}

		if (tempIndex == p_index) {						// if there isn't a new process
			if (processes[p_index].completeTime != -1)	 	// check to see if the current process is done
				quantum[time] = '-';							// if so, then just write a blank
			else {											// else if the current process is still running,
				quantum[time] = processes[p_index].name;;		// label time with process name
				processes[p_index].runTimeRemaining--;			// and decrement the remaining run time
			}
		}
		else {												// if there is new a process,
			if (processes[tempIndex].runTimeRemaining == 0)		// if previous process is done
				processes[tempIndex].completeTime = time;			// then set the complete time 
			processes[p_index].startTime = time;				// set the start time for the next process (new current),
			quantum[time] = processes[p_index].name;			// label time with the new process name,
			processes[p_index].runTimeRemaining--;				// and decrement the remaining run time
		}

		printf("%d, %d, %c, %d\n", time, processes[p_index].runTimeRemaining, quantum[i], p_index);
	}
};
