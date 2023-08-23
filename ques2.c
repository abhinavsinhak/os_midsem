#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the total distance traveled for FCFS
int fcfs(int current, int queue[], int N) {
    int totalDistance = 0;
    for (int i = 0; i < N; i++) {
        totalDistance += abs(current - queue[i]);
        current = queue[i];
    }
    return totalDistance;
}

// Function to calculate the total distance traveled for SSTF
int sstf(int current, int queue[], int N) {
    int totalDistance = 0;
    int remaining = N;
    while (remaining > 0) {
        int shortestDistance = abs(current - queue[0]);
        int shortestIndex = 0;
        for (int i = 1; i < remaining; i++) {
            int distance = abs(current - queue[i]);
            if (distance < shortestDistance) {
                shortestDistance = distance;
                shortestIndex = i;
            }
        }
        totalDistance += shortestDistance;
        current = queue[shortestIndex];
        for (int i = shortestIndex; i < remaining - 1; i++) {
            queue[i] = queue[i + 1];
        }
        remaining--;
    }
    return totalDistance;
}

int main() {
    int current = 21;
    int N;
    printf("Enter the number of pending requests (minimum 12): ");
    scanf("%d", &N);
    if (N < 12) {
        printf("Number of requests must be at least 12.\n");
        return 1;
    }
    int queue[N];
    printf("Enter the %d requests in FIFO order:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &queue[i]);
    }

    // FCFS
    int fcfsDistance = fcfs(current, queue, N);
    printf("Total distance traveled for FCFS: %d\n", fcfsDistance);

    // SSTF
    int sstfDistance = sstf(current, queue, N);
    printf("Total distance traveled for SSTF: %d\n", sstfDistance);

    // Modified algorithm
    int modifiedDistance = 0;
    int remaining = N;
    while (remaining > 0) {
        if (remaining >= 2) {
            modifiedDistance += fcfs(current, queue, 2);
            current = queue[1];
            for (int i = 2; i < remaining; i++) {
                queue[i - 2] = queue[i];
            }
            remaining -= 2;
        }
        modifiedDistance += sstf(current, queue, remaining);
        remaining = 0;
    }
    printf("Total distance traveled for modified algorithm: %d\n", modifiedDistance);

    return 0;
}


/*
Enter the number of pending requests (minimum 12): 12
Enter the 12 requests in FIFO order:
50 75 110 30 85 160 120 10 5 180 200 20

Total distance traveled for FCFS: 855
Total distance traveled for SSTF: 430
Total distance traveled for modified algorithm: 625



*/