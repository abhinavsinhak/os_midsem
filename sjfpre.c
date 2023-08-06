#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h> // Add the stdbool.h library for bool data type

#define MAX_PROC 100

// Process structure
struct Process {
  int pid;
  int art;
  int bt;
  int ct, wt, tat;
};

// Function to find next shortest job
int findShortestJob(struct Process p[], int n, int currentTime) {
  int shortIndex = -1;
  int shortest = INT_MAX; // Change variable name to avoid conflicts

  for (int i = 0; i < n; i++) {
    if (p[i].art <= currentTime && p[i].bt > 0 && p[i].bt < shortest) {
      shortest = p[i].bt;
      shortIndex = i;
    }
  }
  return shortIndex;
}

// SJF preemptive scheduling
void sjfPreemptive(struct Process p[], int n) {
  int total_wt = 0, total_tat = 0;
  int currentTime = 0;
  int completed = 0;

  // Initialize ct, wt, and tat fields of the Process structure
  for (int i = 0; i < n; i++) {
    p[i].ct = p[i].wt = p[i].tat = 0;
  }

  while (completed != n) {
    int shortIndex = findShortestJob(p, n, currentTime);

    if (shortIndex == -1) {
      currentTime++;
    } else {
      // Process the shortest job
      p[shortIndex].ct = currentTime + 1;
      p[shortIndex].bt--;

      currentTime = p[shortIndex].ct;
      
      if (p[shortIndex].bt == 0) {
        completed++;
        p[shortIndex].wt = p[shortIndex].ct - p[shortIndex].art - p[shortIndex].bt;
        p[shortIndex].tat = p[shortIndex].ct - p[shortIndex].art;

        total_wt += p[shortIndex].wt;
        total_tat += p[shortIndex].tat;
      }
    }
  }

  // Print process details
  printf("\nProcess  Arrival  Burst  Completion  Waiting  Turnaround\n");
  for (int i = 0; i < n; i++) {
    printf("   P%d\t    %d\t     %d\t     %d\t      %d\t        %d\n",
      p[i].pid, p[i].art, p[i].bt + p[i].ct - currentTime, p[i].ct, p[i].wt, p[i].tat);
  }

  printf("\nAverage waiting time = %.2f\n", (float)total_wt / n);
  printf("Average turnaround time = %.2f\n", (float)total_tat / n);
}

int main() {

  int n;
  printf("Enter number of processes (max %d): ", MAX_PROC);
  scanf("%d", &n);

  if (n <= 0 || n > MAX_PROC) {
    printf("Invalid number of processes. Please enter a valid number (1-%d).\n", MAX_PROC);
    return 1;
  }

  struct Process p[MAX_PROC];

  for (int i = 0; i < n; i++) {
    printf("Enter arrival time and burst time for P%d: ", i + 1);
    scanf("%d%d", &p[i].art, &p[i].bt);
    p[i].pid = i + 1;
  }

  sjfPreemptive(p, n);

  return 0;
}
