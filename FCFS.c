#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

struct process {
    pid_t real_pid;
    int arrival_time;   // time when process enters ready queue
    int burst_time;     // total time the CPU needs to run the process
    int completion_time;// time when the process finishes its task
    int turnaround_time;// total time from arrival to completion
    int waiting_time;   // total time spent waiting in the ready queue
};

int main (void) {
    int status; // Process Status
    int n;      // Process Quantity Input from the User
    pid_t child_id;
    printf("Input number of processes to be generated (5-10): ");
    scanf("%d", &n);

    sem_t sems[n];
    struct process CP_ID[n]; // not sure what name to call it here

    for (int i = 0; i < n; i++) {
        sem_init(&sems[i], 1, 0);
        child_id = fork();  // Forks creating a child
        if (child_id == 0) { // Check if the process is a child
            break;           // The Child is excluded from forking 
        } else {

        }
        CP_ID[i].real_pid = child_id; // Identification for the child id
    }
        return 0;
}
