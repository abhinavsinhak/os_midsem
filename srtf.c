#include <stdio.h>

// Process structure 
struct Process {
  int pid;
  int arrivalTime;
  int burstTime;
  int remainingTime;
  int startTime;
};

// Function to find next shortest process
int findNextShortest(struct Process* p, int n){
  int shortIndex = -1;
  int shortTime = 9999;

  for(int i=0; i<n; i++){
    if(p[i].remainingTime < shortTime && p[i].remainingTime > 0){
      shortTime = p[i].remainingTime;
      shortIndex = i;
    } 
  }
  return shortIndex;
}

// SRTF scheduling algorithm
void srtf(struct Process* p, int n){
  
  int currentTime = 0;
  int completed = 0;  

  while(completed != n){

    int index = findNextShortest(p, n);

    if(index == -1) 
      currentTime++;

    else{
      if(p[index].remainingTime == p[index].burstTime){
        p[index].startTime = currentTime;
      }

      p[index].remainingTime--; 
      currentTime++;

      if(p[index].remainingTime == 0){
        completed++; 
      }
    }
  }
}

// Print process details 
void printProcessDetails(struct Process* p, int n){

  printf("\nProcess ID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time\n");

  for(int i=0; i<n; i++){

    int completionTime = p[i].startTime + p[i].burstTime;
    int waitingTime = completionTime - p[i].arrivalTime - p[i].burstTime;
    int turnAroundTime = completionTime - p[i].arrivalTime;

    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
           p[i].pid, p[i].arrivalTime, p[i].burstTime, 
           completionTime, waitingTime, turnAroundTime);
  }
}

int main() {

  struct Process p[] = {{1, 0, 6}, {2, 1, 8}, {3, 2, 4}, {4, 3, 5}};

  int n = sizeof(p)/sizeof(p[0]);

  srtf(p, n);

  printProcessDetails(p, n);

  return 0;
}