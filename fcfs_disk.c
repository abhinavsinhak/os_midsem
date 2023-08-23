#include <stdio.h>
int main() {
    int t[20], n, i, tohm[20], tot = 0;
    float avhm;
    
    printf("Enter the number of tracks: ");
    scanf("%d", &n);
    
    printf("Enter the tracks to be traversed: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &t[i]);
        
    tohm[1] = t[1]; // Initialize the first track difference
    
    printf("\nTracks traversed\tDifference between tracks\n");
    printf("%d\t\t\t%d\n", t[1], tohm[1]);
    
    for (i = 2; i <= n; i++) {
        tohm[i] = t[i] - t[i - 1];
        if (tohm[i] < 0)
            tohm[i] = -tohm[i];
        printf("%d\t\t\t%d\n", t[i], tohm[i]);
    }
        
    for (i = 1; i <= n; i++)
        tot += tohm[i];
        
    avhm = (float) tot / n;
    
    printf("\nAverage header movements: %f\n", avhm);
    
    return 0;
}
