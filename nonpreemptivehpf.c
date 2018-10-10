#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "process.c"
#include "priorityQueue.c"

const char * nonpreemptivehpf(struct process *processList, int size) {
    // initialize priority queues. For simplicity, queues[n] is priority n. priority 0 is unused
    // printf("got here 0");
    // getchar();
    struct priorityQueue queues[5];
    queues[1].size = 0;
    queues[2].size = 0;
    queues[3].size = 0;
    queues[4].size = 0;

    // Split up all the processes into priority queues
    // printf("got here 1");
    // getchar();

    int i;
	for (i = 0; i < size; i++){
		queues[processList[i].priority].queue[queues[processList[i].priority].size] = processList[i];
        queues[processList[i].priority].size++;
    }

	// Initialize the output string.
	char output[120];

    // Select the highest priority queue
    int curQueue;
    // initialize the current process index in current priority queue
    int queueIndex;
    // pointer to current process
    struct process * curProcess = NULL;
	
    // printf("got here 2");
    // getchar();
	// Run through time.
	int time;
	for(time = 0; time < 100; ++time) {
        curQueue = 4;
        queueIndex = 0;
        // printf("got here 2.1");
        // getchar();

        bool processRunning = false;
        // if a process is running, then run that one
        if (processRunning) {
            // printf("got here 2.2");
            // getchar();
            // Decrement run time remaining and add to output
            --curProcess->runTimeRemaining;
            // printf("Added proccess name '%c'\n", curProcess->name);
            // getchar();
            output[time] = curProcess->name;
            // if its now done, add its complete time
            if (curProcess->runTimeRemaining == 0) {
                curProcess->completeTime = time + 1;
                processRunning = false;
            }
            // printf("got here 2.2.1");
            // getchar();
            continue;
        }
        // otherwise, look for the next process to be ran

        // find first process (by priority and arrival time) that has arrived and not finished yet
        int i;
        for (i = 0; i < size + 1; i++)
        {
            // printf("got here 2.3");
            // getchar();
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

            // printf("got here 2.4");
            // getchar();

            // If this process has arrived and is not done yet, run it
            if (curProcess->arrivalTime <= time && curProcess->runTimeRemaining != 0) {
                // Check if the process has just started running.
                if(curProcess->runTime == curProcess->runTimeRemaining) {
                    curProcess->startTime = time;
                    processRunning = true;
                }
                // Decrement run time remaining and add to output
                --(curProcess->runTimeRemaining);
			    output[time] = curProcess->name;
                // if its now done, add its complete time
                if (curProcess->runTimeRemaining == 0) {
                    curProcess->completeTime = time + 1;
                    processRunning = false;
                }
                break;
            }
        }

        // printf("Quanta complete. Ran job: %c", output[time]);
        // getchar();
	}

    // printf("got here 3");
    // getchar();

    // Update original process list with starttime and completetime of each process
    for (i = 0; i < size + 1; i++) {
        curQueue = 4;
        queueIndex = 0;

        // find the process matched by name
        int j;
        for (j = 0; j < size; j++)
        {
            // If we've reached the end of the current queue
            // printf("got here 3.1");
            // getchar();
            if(queueIndex == queues[curQueue].size) {
                // if this is the lowest queue, then we are done
                if (curQueue == 1) {
                    break;
                }
                // otherwise, go to the next queue
                curQueue--;
                queueIndex = 0;
                // printf("got here 3.1.1");
                // getchar();
            }

            // printf("got here 3.2");
            // getchar();
            // make a pointer to the current proccess for simplicity
            curProcess = &queues[curQueue].queue[queueIndex];

            // printf("got here 3.3");
            // getchar();

            // if match by name, update its values and break
            if (curProcess->name == processList[i].name) {
                // printf("got here 3.3.1");
                // getchar();
                processList[i].startTime = curProcess->startTime;
                processList[i].completeTime = curProcess->completeTime;
                break;
            }
            // printf("got here 3.4");
            // getchar();
            
            queueIndex++;
        }
    }

    // printf("got here 4");
    // getchar();


	// Ensure that the string is properly terminated.
	output[119] = '\0';

	// Return the string
	return strdup(&output[0]);
}
