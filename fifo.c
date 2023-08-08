#include <stdio.h>
void main()
{
    int refstr[20], s, pages, frames, fault = 0;
    printf("enter the no of pages\n");
    scanf("%d", &pages);
    printf("enter the no of frames\n");
    scanf("%d", &frames);
    for (int i = 0; i < pages; i++)
    {
        printf("enter the %d\n", i + 1);
        scanf("%d", &refstr[i]);
    }
    // input the refrence string
    int temp[frames];
    for (int i = 0; i < frames; i++)
    {
        temp[i] = -1;
    }
    printf("frame1\t frame2\t frame3\n");
    for (int i = 0; i < pages; i++)
    {
        s = 0;
        for (int j = 0; j < frames; j++)
        {
            if (temp[j] == refstr[i])
            {
                s++;
                fault--;
            }
        }
        fault++;
        if (fault <= frames && s == 0)
        {
            temp[i] = refstr[i];
        }
        else if (s == 0)
        {
            temp[(fault - 1) % frames] = refstr[i];
        }
        printf("\n");

        for (int j = 0; j < frames; j++)
        {
            printf("%d\t", temp[j]);
        }
        printf("\n");
    }
    float hitRate = (float)(pages - fault) / pages;
    printf("Page faults = %d\n", fault);
    printf("Hit rate = %.2f", hitRate);
}