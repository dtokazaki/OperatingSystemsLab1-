#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;  

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
	bool change;
	
	// run the algorithm
	for (time=0; time<100;time++) {
		runTimeToken = 11;
		change = false;
		tempIndex = p_index;
		for (i=0;i<10;i++) {
			if (processes[i].arrivalTime <= time && processes[i].runTimeRemaining < runTimeToken && processes[i].runTimeRemaining > 0) { // lots of conditions
				p_index = i; 								// update the index to the next processes
				runTimeToken = processes[p_index].runTimeRemaining;  // update the runTimeToken
				change = true;
			} 
		}
		
		if (!change) {				// if there was no change in p_index	
			if (processes[p_index].runTimeRemaining > 0 && processes[p_index].arrivalTime<=time) {	   // if same process still running
			    if (processes[p_index].runTimeRemaining == processes[p_index].runTime)
			        processes[p_index].startTime = time;
			    quantum[time] = processes[p_index].name;		
				printf("%c\n", processes[p_index].name);
				processes[p_index].runTimeRemaining--;
			}
			else if (processes[p_index].completeTime == 0 && processes[p_index].runTimeRemaining == 0) {  // if same process has ended
			    quantum[time] = '-';	
				printf("%c\n", '-');
			    processes[tempIndex].completeTime = time-1;
			}
			else {						    // there is no process running
				quantum[time] = '-';	
				printf("%c\n", '-');
			}
		}
		else {					// if the p_index changed						
			if (processes[tempIndex].runTimeRemaining == 0 && processes[tempIndex].completeTime == 0)	 // if previous process is complete
				processes[tempIndex].completeTime = time-1;			
			if  (processes[p_index].runTimeRemaining == processes[p_index].runTime)
			    processes[p_index].startTime = time;				
			quantum[time] = processes[p_index].name;			
			printf("%c\n", processes[p_index].name);
			processes[p_index].runTimeRemaining--;				
		}

		printf("%d, %d, %c, %d, %d, %d\n", time, processes[p_index].runTimeRemaining, quantum[i], p_index,processes[tempIndex].startTime, processes[tempIndex].completeTime);
	}
};
