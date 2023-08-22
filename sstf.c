#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf(int request_queue[], int head, int n) {
    int seek_sequence[n];
    int cur_track = head;
    int distance, cur_distance, cur_index, total_seek_time = 0;
    int visited[n];
  
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
  
    for (int i = 0; i < n; i++) {
        cur_distance = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                distance = abs(request_queue[j] - cur_track);
                if (distance < cur_distance) {
                    cur_index = j;
                    cur_distance = distance;
                }
            }
        }
  
        visited[cur_index] = 1;
        seek_sequence[i] = request_queue[cur_index];
        total_seek_time += cur_distance;  // Calculate seek time
        cur_track = request_queue[cur_index];
    }
  
    printf("Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int request_queue[] = {98, 183, 37, 122, 14, 124, 65, 67, 189, 2, 187, 193};
    int head, n;

    n = sizeof(request_queue) / sizeof(request_queue[0]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    sstf(request_queue, head, n);

    return 0;
}
