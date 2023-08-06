#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int A, vector<vector<int>>& arr) {
    int M = arr.size(); // Number of types of work

    vector<int> B(M), D(M); // Vectors to store the deadlines and days to complete

    for (int i = 0; i < M; i++) {
        B[i] = arr[i][1];
        D[i] = arr[i][2];
    }

    vector<int> days(A + 1, -1); // Initialize with -1, indicating rest days

    for (int i = 0; i < M; i++) {
        int workType = arr[i][0];
        int deadlineDay = B[i];
        int daysToComplete = D[i];

        for (int j = deadlineDay; j <= min(A, deadlineDay + daysToComplete - 1); j++) {
            days[j] = workType; // Assign the work type only if not assigned before or lower priority
        }
    }

    vector<int> result;
    for (int i = 1; i <= A; i++) {
        if (days[i] == -1) {
            days[i] = 0; // Mark rest days as 0
        }
        result.push_back(days[i]);
    }

    return result;
}

int main() {
    int A = 6; // Number of days in a year

    vector<vector<int>> arr = {{1, 3, 1}, {1, 6, 1}, {1, 2, 1}}; // Work types and their details

    vector<int> result = solve(A, arr);

    cout << "Output: ";
    for (int day : result) {
        cout << day << " ";
    }
    cout << endl;

    return 0;
}
