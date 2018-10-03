#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printqueue(struct process *array, int size) {
	
	int i;
	
	for(i=0;i<size;i++) {	
		fprintf(stdout, "Name: %s Priority: %d \n",array[size]->name,arrau[size]->priority );
	}
}




char* roundrobin(struct process *array) {

	int i;
	int size = 10;										// Total number of processes 
	struct process priority1[size];
	struct process priority2[size];
	struct process priority3[size];								// 4 Different priority queues
	struct process priority4[size];
	int 1_pos = 0;									
	int 2_pos = 0;										// Number of processes in each of the queues
	int 3_pos = 0;
	int 4_pos = 0;
	int quanta = 0;
	
	for(i=0;i<size;i++) {									// Loop through all of the processes and copy each one to its respective priority queue
		switch(array[size]->priority) {

			case 1:
				priority1[1_pos] = array[size];
				1_pos++;
				break;	
			case 2:
				priority2[2_pos] = array[size];
				2_pos++;
				break;
			case 3:
				priority3[3_pos] = array[size];
				3_pos++;
				break;
			case 4:
				priority4[4_pos] = array[size];
				4pos++;
				break;
			default:
				fprintf(stdout, "Unexpected priority level \n");

		}
	}

	
}

