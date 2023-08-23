#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h> // Add the stdbool.h library for bool data type

//strucutre to store process and arrival time and burst time
struct process
{
    int WT, AT, BT, TAT, PT;
};
//implement round robin algorithm
void round_robin()
{
    int n, i, j, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remain = n;
    int arrival_time[n], burst_time[n], rt[n];
    printf("Enter the arrival time and burst time:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        rt[i] = burst_time[i];
    }
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for (time = 0, i = 0; remain != 0;)
    {
        if (rt[i] <= time_quantum && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if (rt[i] > 0)
        {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        if (rt[i] == 0 && flag == 1)
        {
            remain--;
            printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time - arrival_time[i], time - arrival_time[i] - burst_time[i]);
            wait_time += time - arrival_time[i] - burst_time[i];
            turnaround_time += time - arrival_time[i];
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (arrival_time[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    printf("\nAverage Waiting Time= %f\n", wait_time * 1.0 / n);
    printf("Avg Turnaround Time = %f\n", turnaround_time * 1.0 / n);
}
//write main function for round robin 
int main()
{
    round_robin();
    return 0;
}