#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <fcntl.h>

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

    do {
        printf("Input number of processes to be generated (5-10): ");
        scanf("%d", &n);
        int result = scanf("%d", &n);
        if (result == (n < 5 || n > 10)) {
            printf("ERROR: Choose a valid number!");
            continue;
        } else if () {

        }
    } while() ;

    sem_t *start_sems[n];
    sem_t *end_sems[n];
    struct process CP_ID[n]; // not sure what name to call it here
    srand(time(NULL));       // True Randomization

    int i;
    for (i = 0; i < n; i++) {
        // Initializing the semaphores (MacOS version)
        char name[32];
        snprintf(name, sizeof(name), "/start_%d", i);
        start_sems[i] = sem_open(name, O_CREAT, 0644, 0);

        snprintf(name, sizeof(name), "/end_%d", i);
        end_sems[i] = sem_open(name, O_CREAT, 0644, 0);


        /*  ON LINUX:
        sem_init(&start_sems[i], 1, 0);
        sem_init(&end_sems[i], 1, 0);
        */ 
        CP_ID[i].burst_time = (rand() % 5) + 1; // 1-5 seconds
        child_id = fork();  // Forks creating a child
        if (child_id == 0) { // Check if the process is a child
            break;           // The Child is excluded from forking 
        }
        CP_ID[i].real_pid = child_id; // Identification for the child id
        printf("Process %d (PID: %d) created, burst: %d\n", i, child_id, CP_ID[i].burst_time);
    }

    if (child_id == 0) {
        sem_wait(start_sems[i]);
        sleep(CP_ID[i].burst_time);
        printf("Process %d (PID: %d) executing\n", i, getpid());
        sem_post(end_sems[i]); // to signal the end
        exit(0);
    } else {    // Parent process
        sem_post(start_sems[0]);      // Parent process upholding the other processes
        for (int i = 0; i < n; i++) {
            sem_wait(end_sems[i]);
            waitpid(CP_ID[i].real_pid, &status, 0); // Generating the waits for the children, returns 0 while child is still alive 
            if (i < n - 1) {
                sem_post(start_sems[i+1]);
            }
        }
    }
        return 0;
}
