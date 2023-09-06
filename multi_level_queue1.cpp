#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent a process
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
};

// Comparator for SJF queue
struct SJFComparator
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.burst_time > p2.burst_time;
    }
};

int main()
{
    // Create FCFS and SJF queues
    queue<Process> fcfsQueue;
    priority_queue<Process, vector<Process>, SJFComparator> sjfQueue;

    // Example processes
    Process p1 = {1, 0, 6, 0, 0};
    Process p2 = {2, 1, 4, 0, 0};
    Process p3 = {3, 2, 8, 0, 0};
    Process p4 = {4, 3, 2, 0, 0};

    // Enqueue processes into the FCFS queue
    fcfsQueue.push(p1);
    fcfsQueue.push(p3);

    // Enqueue processes into the SJF queue
    sjfQueue.push(p2);

    // Current time
    int time = 0;

    while (!fcfsQueue.empty() || !sjfQueue.empty())
    {
        if (!sjfQueue.empty())
        {
            Process currentProcess = sjfQueue.top();
            sjfQueue.pop();

            cout << "Time " << time << ": Executing Process " << currentProcess.id << endl;

            currentProcess.turnaround_time = time - currentProcess.arrival_time;
            currentProcess.waiting_time = currentProcess.turnaround_time - currentProcess.burst_time;

            time += currentProcess.burst_time;

            cout << "Turnaround Time for Process " << currentProcess.id << ": " << currentProcess.turnaround_time << endl;
            cout << "Waiting Time for Process " << currentProcess.id << ": " << currentProcess.waiting_time << endl;
        }
        else if (!fcfsQueue.empty())
        {
            Process currentProcess = fcfsQueue.front();
            fcfsQueue.pop();

            cout << "Time " << time << ": Executing Process " << currentProcess.id << endl;

            currentProcess.turnaround_time = time - currentProcess.arrival_time;
            currentProcess.waiting_time = currentProcess.turnaround_time - currentProcess.burst_time;

            time += currentProcess.burst_time;

            cout << "Turnaround Time for Process " << currentProcess.id << ": " << currentProcess.turnaround_time << endl;
            cout << "Waiting Time for Process " << currentProcess.id << ": " << currentProcess.waiting_time << endl;
        }
    }

    return 0;
}