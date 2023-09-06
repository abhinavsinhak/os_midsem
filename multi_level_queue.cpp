#include <stdio.h>
#include <stdlib.h>

// Define a structure for a process
typedef struct {
    int process_id;
    int burst_time;
    int arrival_time;
} Process;

// Define a structure for a queue
typedef struct {
    Process* array;
    int front, rear;
    unsigned capacity;
} Queue;

// Function to create a new queue
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->array = (Process*)malloc(capacity * sizeof(Process));
    queue->front = queue->rear = -1;
    return queue;
}

// Function to check if a queue is empty
int isEmpty(Queue* queue) {
    return queue->front == -1;
}

// Function to check if a queue is full
int isFull(Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Function to enqueue a process into the queue
void enqueue(Queue* queue, Process process) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }
    queue->array[queue->rear] = process;
}

// Function to dequeue a process from the queue
Process dequeue(Queue* queue) {
    Process process;
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        process.process_id = -1;
        process.burst_time = -1;
        return process;
    }
    process = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return process;
}

// Function to execute processes in FCFS queue
void executeFCFS(Queue* fcfsQueue) {
    printf("Executing processes in FCFS order:\n");
    while (!isEmpty(fcfsQueue)) {
        Process process = dequeue(fcfsQueue);
        printf("Process %d with burst time %d\n", process.process_id, process.burst_time);
    }
}

// Function to sort processes based on burst time and arrival time for SJF
void sortByArrivalTime(Process* processes, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].burst_time > processes[j + 1].burst_time)) {
                // Swap processes[j] and processes[j+1]
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to execute processes in SJF queue
void executeSJF(Process* processes, int n) {
    printf("Executing processes in SJF order:\n");
    sortByArrivalTime(processes, n);
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > currentTime) {
            currentTime = processes[i].arrival_time;
        }
        printf("Process %d with burst time %d\n", processes[i].process_id, processes[i].burst_time);
        currentTime += processes[i].burst_time;
    }
}

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Queue* fcfsQueue = createQueue(numProcesses);
    Process* sjfProcesses = (Process*)malloc(numProcesses * sizeof(Process));

    for (int i = 0; i < numProcesses; i++) {
        Process process;
        process.process_id = i + 1;
        printf("Enter arrival time for Process %d: ", process.process_id);
        scanf("%d", &process.arrival_time);
        printf("Enter burst time for Process %d: ", process.process_id);
        scanf("%d", &process.burst_time);
        enqueue(fcfsQueue, process);
        sjfProcesses[i] = process;
    }

    executeFCFS(fcfsQueue);
    executeSJF(sjfProcesses, numProcesses);

    free(fcfsQueue->array);
    free(fcfsQueue);
    free(sjfProcesses);

    return 0;
}
