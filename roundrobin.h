
void printQueue(struct process *array);
void run(struct process *array,int &pos, int &proc_left, int &quanta, char *timetable);
void avail(struct process *array, int &pos, int quanta);
char *roundRobin(struct process *array);
