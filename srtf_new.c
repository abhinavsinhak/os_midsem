#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
//implement sjf preemptive from my repo sjfpre.c
#define MAX_PROC 100
struct Process
{
    int pid;
    int art;
    int bt;
    int ct, wt, tat;
};
int findShortestJob(struct Process p[], int n, int currentTime)
{
    int shortIndex = -1;
    int shortest = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (p[i].art <= currentTime && p[i].bt > 0 && p[i].bt < shortest)
        {
            shortest = p[i].bt;
            shortIndex = i;
        }
    }
    return shortIndex;
}
void sjf_preemptive()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].art);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
    }
    int total_wt = 0, total_tat = 0;
    int currentTime = 0;
    int completed = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].ct = p[i].wt = p[i].tat = 0;
    }
    while (completed != n)
    {
        int shortIndex = findShortestJob(p, n, currentTime);
        if (shortIndex == -1)
        {
            currentTime++;
        }
        else
        {
            p[shortIndex].ct = currentTime + 1;
            p[shortIndex].bt--;
            currentTime = p[shortIndex].ct;
            if (p[shortIndex].bt == 0)
            {
                completed++;
                p[shortIndex].wt = p[shortIndex].ct - p[shortIndex].art - p[shortIndex].bt;
                p[shortIndex].tat = p[shortIndex].ct - p[shortIndex].art;
                total_wt += p[shortIndex].wt;
                total_tat += p[shortIndex].tat;
            }
        }
    }
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\tResponse Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].art, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].wt);
    }
    printf("Average waiting time: %f\n", (float)total_wt / n);
    printf("Average turnaround time: %f\n", (float)total_tat / n);
}
int main()
{
    sjf_preemptive();
    return 0;
}