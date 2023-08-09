#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
};

void multiLevelQueue(vector<queue<Process>>& queues, int timeQuantum) {
    for (int i = 0; i < queues.size(); i++) {
        while (!queues[i].empty()) {
            Process p = queues[i].front();
            queues[i].pop();
            
            if (p.burstTime > timeQuantum) {
                p.burstTime -= timeQuantum;
                cout << "Process " << p.id + 1 << " from Queue " << i + 1 << " executed for " << timeQuantum << " units." << endl;
                queues[i].push(p);
            } else {
                cout << "Process " << p.id + 1 << " from Queue " << i + 1 << " executed for " << p.burstTime << " units." << endl;
            }
        }
    }
}

int main() {
    int numQueues, numProcesses, timeQuantum;

    cout << "Enter the number of queues: ";
    cin >> numQueues;

    vector<queue<Process>> queues(numQueues);

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        queues[0].push(processes[i]);
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    multiLevelQueue(queues, timeQuantum);

    return 0;
}
