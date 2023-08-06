#include <stdio.h>

#define MAX_FRAMES 3

int findLRU(int time[], int n)
{
    int i, min = time[0], pos = 0;

    for (i = 1; i < n; ++i)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }

    return pos;
}

int main()
{

    int frames[MAX_FRAMES];
    int pages[20]; // Increased size to allow user input
    int n;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    int time[MAX_FRAMES];

    // Initialize frames and time
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
        time[i] = -1;
    }

    int hit = 0;

    printf("Frame1\tFrame2\tFrame3\n");

    for (int i = 0; i < n; i++)
    {

        int found = 0;
        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                time[j] = i;
                hit++;
                break;
            }
        }

        if (!found)
        {
            int lru = findLRU(time, MAX_FRAMES);
            frames[lru] = pages[i];
            time[lru] = i;
        }

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }

    int faults = n - hit; // Calculate faults
    float hitRate = (float)hit / n;

    printf("Page faults = %d\n", faults);
    printf("Hit rate = %.2f", hitRate);

    return 0;
}