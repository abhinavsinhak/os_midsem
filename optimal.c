#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 12

int main()
{
    int frames[MAX_FRAMES], pages[MAX_FRAMES];
    int n, m, hits = 0, faults = 0;

    printf("Enter the number of frames (maximum %d): ", MAX_FRAMES);
    scanf("%d", &m);

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page references: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    // Initialize frames to -1 indicating an empty frame
    for (int i = 0; i < m; i++)
    {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        bool hit = false;

        // Check if the page is already in the frames
        for (int j = 0; j < m; j++)
        {
            if (frames[j] == page)
            {
                hit = true;
                hits++;
                break;
            }
        }

        if (!hit)
        {
            int replace_page = -1;
            int farthest = i + 1; // Initialize farthest as the next index

            // Find the page that will not be used for the longest time
            for (int j = 0; j < m; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        break;
                    }
                }
                if (k == n)
                {
                    replace_page = j;
                    break;
                }
                if (k > farthest)
                {
                    farthest = k;
                    replace_page = j;
                }
            }

            faults++;
            frames[replace_page] = page;
        }

        // Display the current frames
        printf("Frames: ");
        for (int j = 0; j < m; j++)
        {
            if (frames[j] == -1)
            {
                printf("- ");
            }
            else
            {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Hits: %d\n", hits);
    printf("Total Page Faults: %d\n", faults);

    return 0;
}
