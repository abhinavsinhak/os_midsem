#include <stdio.h>
//structure to store the process and arrival time and burst time
struct process
{
    int WT, AT, BT, TAT, PT;
};
//implement fcfs algorithm for cpu scheduling
void fcfs()
{
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    printf("Enter the arrival time and burst time:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }
    int ct[n];
    ct[0] = p[0].AT + p[0].BT;
    for (i = 1; i < n; i++)
    {
        if (ct[i - 1] > p[i].AT)
            ct[i] = ct[i - 1] + p[i].BT;
        else
            ct[i] = p[i].AT + p[i].BT;
    }
    int tat[n];
    int wt[n];
    int sum_tat = 0, sum_wt = 0;
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - p[i].AT;
        wt[i] = tat[i] - p[i].BT;
        sum_tat += tat[i];
        sum_wt += wt[i];
    }
    printf("AT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].AT, p[i].BT, ct[i], tat[i], wt[i]);
    }
    printf("Average Turnaround Time = %f\n", sum_tat * 1.0 / n);
    printf("Average Waiting Time = %f\n", sum_wt * 1.0 / n);
}
//main function for fcfs
int main()
{
    fcfs();
    return 0;
}