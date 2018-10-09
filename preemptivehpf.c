#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "process.c"

struct priorityQueue {
        struct process queue[15];
        int size;
    };

const char * preemptivehpf(struct process *processList, int size) {
    // initialize priority queues. For simplicity, queues[n] is priority n. priority 0 is unused
    struct priorityQueue queues[4];
    queues[1].size = 0;
    queues[2].size = 0;
    queues[3].size = 0;
    queues[4].size = 0;

    // Split up all the processes into priority queues
    int i;
	for (i = 0; i < size; i++) {
		queues[processList[i].priority].queue[queues[processList[i].priority].size++] = processList[i];
    }

	// Initialize the output string.
	char output[101];

    // Select the highest priority queue
    int curQueue;
    // initialize the current process index in current priority queue
    int queueIndex;
    // pointer to current process
    struct process * curProcess;
	
	// Run through time.
	int time;
	for(time = 0; time < 100; ++time) {
        curQueue = 4;
        queueIndex = 0;

        // find first process (by priority and arrival time) that has arrived and not finished yet
        int i;
        for (i = 0; i < size; i++)
        {
            // If we've reached the end of the current queue
            if(queueIndex == queues[curQueue].size) {
                // if this is the lowest queue, then no processes are ready to run right now
                if (curQueue == 1) {
                    output[time] = '-';
                    break;
                }
                // otherwise, go to the next queue
                curQueue--;
                queueIndex = 0;
            }

            // make a pointer to the current proccess for simplicity
            curProcess = &queues[curQueue].queue[queueIndex];

            // If this process has arrived and is not done yet, run it
            if (curProcess->arrivalTime <= time && curProcess->runTimeRemaining != 0) {
                // Check if the process has just started running.
                if(curProcess->runTime == curProcess->runTimeRemaining) {
                    curProcess->startTime = time;
                }
                // Decrement run time remaining and add to output
                --(curProcess->runTimeRemaining);
			    output[time] = curProcess->name;
                // if its now done, add its complete time
                if (curProcess->runTimeRemaining == 0) {
                    curProcess->completeTime = time + 1;
                }
                break;
            } else {
                queueIndex++;
            }
        }
	}

	// Ensure that the string is properly terminated.
	output[100] = '\0';

	// Return the string
	return strdup(&output[0]);
}
