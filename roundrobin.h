/*
* This file is the headeer file for the Round Robin Scheduling Algorithm
*
* COEN 383 Advanced operating systems
* Fall Quarter 2018
*
*/

#ifndef COEN383_LAB1
#define COEN383_LAB1

/*
* void printQueue(struct process *array, int size)
* PrintQueue is a function that takes the process struct and the amount of processes in the struct as input parameters. The struct is then printed out.
*
* void run(struct process *array, int *pos, int *proc_list, int *quanta, int size, char *timetable)
* Run is the main function in the Round Robin algorithm. The struct, the position of a specific process, the amount of processes left in the queue, the total size of the queue, and a string is
* passed into the function. If the process hasnt been started yet, and the quanta is currently less then 99, the current quanta becomes the start time. The time remaining is then decremented,
* the quanta is incremented, and the name of the process is appended to the string timetable. If the timeRemaining is 0, we then decrement the proc_list and set the completed time as the current quanta.
*
* int avail(struct process *array, int pos, int quanta, int size)
* avail is a function that checks to see if the process at a given index in the queue is currently ready to run. The time remaining must be greater than 0 and the arrival time must be less than or equal to 
* the current quanta. If no process is ready to run, -1 is returned, otherwise the index of the process is returned.
*
* char *roundrobin(struct process * array)
* This function runs the Round Robin algorithm, and is called by main.
*/
	
void printQueue(struct process *array, int size);
void run(struct process *array, int *pos, int *proc_left, int *quanta,int *size, char *timetable);
int avail(struct process *array, int pos, int quanta, int size);
char *roundRobin(struct process *array);

#endif
