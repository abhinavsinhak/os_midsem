#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
} Process;

void preemptivePriorityScheduling(Process processes[], int n) {
    int currentTime = 0;
    int completedProcesses = 0;
    int remainingTime[MAX_PROCESSES];
    int remainingPriority[MAX_PROCESSES];
    int isCompleted[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burst_time;
        remainingPriority[i] = processes[i].priority;
        isCompleted[i] = 0;
    }

    printf("Gantt Chart:\n");
    while (completedProcesses < n) {
        int highestPriority = -1;
        int selectedProcess = -1;

        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrival_time <= currentTime && remainingPriority[i] > highestPriority) {
                highestPriority = remainingPriority[i];
                selectedProcess = i;
            }
        }

        if (selectedProcess != -1) {
            if (remainingTime[selectedProcess] > 0) {
                printf("%d - P%d ", currentTime, processes[selectedProcess].process_id);
                remainingTime[selectedProcess]--;
                remainingPriority[selectedProcess]--;
                currentTime++;

                if (remainingTime[selectedProcess] == 0) {
                    isCompleted[selectedProcess] = 1;
                    completedProcesses++;
                }
            }
        } else {
            printf("%d - Idle ", currentTime);
            currentTime++;
        }
    }
    printf("%d\n", currentTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    preemptivePriorityScheduling(processes, n);

    // Calculate turnaround time and waiting time
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        int turnaroundTime = currentTime - processes[i].arrival_time;
        int waitingTime = turnaroundTime - processes[i].burst_time;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
    }

    printf("\nTurnaround Time:\n");
    for (int i = 0; i < n; i++) {
        int turnaroundTime = currentTime - processes[i].arrival_time;
        printf("P%d: %d\n", processes[i].process_id, turnaroundTime);
    }

    printf("\nWaiting Time:\n");
    for (int i = 0; i < n; i++) {
        int turnaroundTime = currentTime - processes[i].arrival_time;
        int waitingTime = turnaroundTime - processes[i].burst_time;
        printf("P%d: %d\n", processes[i].process_id, waitingTime);
    }

    return 0;
}
