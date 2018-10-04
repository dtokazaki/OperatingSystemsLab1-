/*
* This file is the headeer file for the Round Robin Scheduling Algorithm
*
* COEN 383 Advanced operating systems
* Fall Quarter 2018
*
*/

void printQueue(struct process *array, int size);
void run(struct process *array,int &pos, int &proc_left, int &quanta, char *timetable);
void avail(struct process *array, int &pos, int quanta, int size);
char *roundRobin(struct process *array);
