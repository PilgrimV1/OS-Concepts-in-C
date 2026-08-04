#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct process {
    int time_loaded;
    int time_exited;
    int turnaround_time;
};

int main (void) {
    int status; // Process Status
    pid_t child_id;

    child_id = fork ();

    if (child_id == 0) {
        printf("Child Process ID: %d\n", getpid());
    } else { // Parent process waits
        if (wait(&status) != child_id) {
            printf("ERROR: Parent process failed to wait!\n"); 
        } else {
            printf("Child Process has been successfully terminated with the status: %d\n", status);
        }
    }
    return 0;

}
