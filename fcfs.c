#include <stdio.h>

#define MAX_PROCESSES 100

void sort(int* a, int* b, int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int key = a[i];
        int pro_key = b[i];
        while (j >= 0 && key < a[j]) {
            a[j + 1] = a[j];
            b[j + 1] = b[j];
            j--;
        }
        a[j + 1] = key;
        b[j + 1] = pro_key;
    }
}

int main() {
    int no_of_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &no_of_processes);
    printf("\n");

    int at[MAX_PROCESSES];
    int bt[MAX_PROCESSES];

    printf("Enter arrival time and burst time:\n");
    for (int i = 0; i < no_of_processes; i++) {
        scanf("%d %d", &at[i], &bt[i]);
    }
    printf("\n");

    sort(at, bt, no_of_processes);

    int ct[MAX_PROCESSES];
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < no_of_processes; i++) {
        if (ct[i - 1] > at[i])
            ct[i] = ct[i - 1] + bt[i];
        else
            ct[i] = at[i] + bt[i];
    }

    int tat[MAX_PROCESSES];
    int wt[MAX_PROCESSES];
    int sum_tat = 0, sum_wt = 0;
    for (int i = 0; i < no_of_processes; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sum_tat += tat[i];
        sum_wt += wt[i];
    }

    printf("at\tbt\tct\ttat\twt\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Avg Turnaround Time: %0.2f\nAvg Waiting Time: %0.2f\n",(float)sum_tat / no_of_processes,(float) sum_wt / no_of_processes);

    return 0;
}
