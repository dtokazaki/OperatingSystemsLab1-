/*
* This file is the headeer file for the Round Robin Scheduling Algorithm
*
* COEN 383 Advanced operating systems
* Fall Quarter 2018
*
*/

#ifndef COEM383_LAB1
#define COEN383_LAB1

void printQueue(struct Process *array, int size);
void run(struct Process *array, int *pos, int *proc_left, int *quanta, char *timetable);
int avail(struct Process *array, int pos, int quanta, int size);
char *roundRobin(struct Process *array);

#endif
