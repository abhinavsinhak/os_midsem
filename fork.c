#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FRAMES 3 // Maximum number of page frames

// Function to implement FIFO algorithm
void fifo(int *frames, int n, int page) {
    static int front = 0;
    static int rear = 0;

    if (frames[rear] == -1) {
        frames[rear] = page;
        rear = (rear + 1) % n;
    } else {
        frames[front] = page;
        front = (front + 1) % n;
    }
}

// Function to implement LRU algorithm
void lru(int *frames, int n, int page) {
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < n - 1; i++) {
            frames[i] = frames[i + 1];
        }
        frames[n - 1] = page;
    } else {
        for (int i = 0; i < n - 1; i++) {
            frames[i] = frames[i + 1];
        }
        frames[n - 1] = page;
    }
}

int main() {
    int frames[MAX_FRAMES] = {-1};
    int page, choice;

    printf("Enter the page reference sequence (end with -1):\n");

    while (1) {
        scanf("%d", &page);
        if (page == -1) break;

        printf("Choose replacement algorithm (0 for FIFO, 1 for LRU): ");
        scanf("%d", &choice);

        if (fork() == 0) { // Child process (FIFO)
            fifo(frames, MAX_FRAMES, page);
            printf("Child Process (FIFO): ");
        } else { // Parent process (LRU)
            lru(frames, MAX_FRAMES, page);
            printf("Parent Process (LRU): ");
        }

        // Print the current state of page frames
        for (int i = 0; i < MAX_FRAMES; i++) {
            if (frames[i] == -1)
                printf(" -");
            else
                printf(" %d", frames[i]);
        }
        printf("\n");
    }

    return 0;
}
