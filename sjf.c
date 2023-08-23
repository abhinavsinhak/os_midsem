#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct process
{
    int arrival_time;
    int burst_time;
    int pid;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int flag;
};
//sjf function
void sjf()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].flag = 0;
    }
    int time = 0;
    int count = 0;
    int min = 1000;
    int index = 0;
    while (count != n)
    {
        for (i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time && p[i].flag == 0)
            {
                if (p[i].burst_time < min)
                {
                    min = p[i].burst_time;
                    index = i;
                }
            }
        }
        p[index].flag = 1;
        p[index].completion_time = time + p[index].burst_time;
        p[index].turn_around_time = p[index].completion_time - p[index].arrival_time;
        p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
        p[index].response_time = p[index].waiting_time;
        time = p[index].completion_time;
        count++;
        min = 1000;
    }
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\tResponse Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }
}
//write the main function to call the sjf function
int main()
{
    sjf();
    return 0;
}