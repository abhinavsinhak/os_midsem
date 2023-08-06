#include <stdio.h>

// Structure to represent a process
struct Process {
  int pid; // Process ID
  int bt; // Burst time
  int art; // Arrival time 
};

// FCFS scheduling function
void FCFS(struct Process proc[], int n) {
  
  int wt[n], tat[n], total_wt = 0, total_tat = 0;

  // Sort processes by arrival time
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
      if(proc[i].art > proc[j].art) {
        struct Process temp = proc[i];
        proc[i] = proc[j];
        proc[j] = temp;
      }
    }
  }

  // Find completion times
  int ct[n];
  ct[0] = proc[0].art + proc[0].bt;
  for(int i=1; i<n; i++) {
    ct[i] = ct[i-1] + proc[i].bt;
  }
  
  // Calculate waiting times
  for(int i=0; i<n; i++) {
    wt[i] = ct[i] - proc[i].bt - proc[i].art;
    total_wt += wt[i];
  }

  // Calculate turnaround times
  for(int i=0; i<n; i++) {
    tat[i] = ct[i] - proc[i].art;
    total_tat += tat[i];
  }

  // Print process details
  printf("Processes  Burst Time  Arrival Time  Completion Time  Waiting Time  Turn Around Time\n");
  for(int i=0; i<n; i++) {
    printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].art, ct[i], wt[i], tat[i]);
  }

  // Print average waiting and turnaround times
  printf("Average waiting time = %f\n", (float)total_wt / n); 
  printf("Average turnaround time = %f\n", (float)total_tat / n);
}

int main() {
  
  struct Process proc[] = { {1, 6, 1}, {2, 8, 0}, {3, 7, 2}, {4, 3, 4} };
  int n = sizeof(proc)/sizeof(proc[0]);

  FCFS(proc, n);

  return 0;
}