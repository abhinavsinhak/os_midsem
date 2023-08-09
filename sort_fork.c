#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n, int isAscending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((isAscending && arr[j] > arr[j + 1]) || (!isAscending && arr[j] < arr[j + 1])) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {9, 3, 7, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process sorting elements in descending order...\n");
        bubbleSort(arr, n, 0);
    } else {
        // Parent process
        printf("Parent process sorting elements in ascending order...\n");
        bubbleSort(arr, n, 1);
        wait(NULL); // Wait for the child process to finish
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
