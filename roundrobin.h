/*
* This file is the headeer file for the Round Robin Scheduling Algorithm
*
* COEN 383 Advanced operating systems
* Fall Quarter 2018
*
*/

#include "fcfs.c"

void printQueue(struct Process *array, int size);
void run(struct Process *array,int &pos, int &proc_left, int &quanta, char *timetable);
void avail(struct Process *array, int &pos, int quanta, int size);
char *roundRobin(struct Process *array);
