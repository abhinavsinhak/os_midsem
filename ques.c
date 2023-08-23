#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
};

void calculate_metrics(struct Process processes[], int n, int turnaround_time[], int waiting_time[], float *avg_turnaround, float *avg_waiting) {
    int total_turnaround = 0;
    int total_waiting = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround += turnaround_time[i];
        total_waiting += waiting_time[i];
    }

    *avg_turnaround = (float)total_turnaround / n;
    *avg_waiting = (float)total_waiting / n;
}

void priority_scheduling(struct Process processes[], int n, int ratio, float *avg_turnaround, float *avg_waiting) {
    int turnaround_time[n];
    int waiting_time[n];
    int remaining_burst_time[n];
    int current_time = 0;
    int executed[n];
    int executed_process_count;

    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
        executed[i] = 0;
    }

    while (1) {
        int ready_queue[n];
        int ready_queue_size = 0;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !executed[i]) {
                ready_queue[ready_queue_size++] = i;
            }
        }

        if (ready_queue_size == 0) {
            break;
        }

        for (int i = 0; i < ready_queue_size; i++) {
            for (int j = i + 1; j < ready_queue_size; j++) {
                if (processes[ready_queue[i]].priority < processes[ready_queue[j]].priority) {
                    int temp = ready_queue[i];
                    ready_queue[i] = ready_queue[j];
                    ready_queue[j] = temp;
                }
            }
        }

        executed_process_count = (ready_queue_size < 3) ? ready_queue_size : 3;

        for (int i = 0; i < executed_process_count; i++) {
            int selected_process = ready_queue[i];

            if (ratio && i % ratio == ratio - 1) {
                selected_process = ready_queue[ready_queue_size - 1];
            }

            waiting_time[selected_process] = current_time - processes[selected_process].arrival_time;
            current_time += remaining_burst_time[selected_process];
            turnaround_time[selected_process] = current_time - processes[selected_process].arrival_time;
            remaining_burst_time[selected_process] = 0;
            executed[selected_process] = 1;
        }
    }

    calculate_metrics(processes, n, turnaround_time, waiting_time, avg_turnaround, avg_waiting);
}

int main() {
    struct Process processes[] = {
        {1, 0, 10, 3},
        {2, 1, 4, 1},
        {3, 2, 5, 2},
        {4, 3, 3, 2},
        {5, 4, 8, 1}
    };

    int n = sizeof(processes) / sizeof(processes[0]);
    float avg_turnaround_fcfs, avg_waiting_fcfs, avg_turnaround_modified, avg_waiting_modified;
    int ratio = 2;

    priority_scheduling(processes, n, 0, &avg_turnaround_fcfs, &avg_waiting_fcfs);
    printf("Original Policy (No Ratio):\n");
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_fcfs);
    printf("Average Waiting Time: %.2f\n\n", avg_waiting_fcfs);

    priority_scheduling(processes, n, ratio, &avg_turnaround_modified, &avg_waiting_modified);
    printf("Modified Policy with %d:1 Ratio:\n", ratio);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_modified);
    printf("Average Waiting Time: %.2f\n", avg_waiting_modified);

    return 0;
}
