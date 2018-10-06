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
		if (processes[p_index].runTimeRemaining != 0 && time>=processes[p_index].arrivalTime){		// check if process is still running
		    printf("%c\n", processes[p_index].name);
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
		printf("%d, %d, %c, %d\n", time, processes[p_index].runTimeRemaining, quantum[i], p_index);
	}

};
