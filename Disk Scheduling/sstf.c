#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void difference(int request[], int head, int diff[][2], int n) {
    for (int i = 0; i < n; i++) {
        diff[i][0] = abs(head - request[i]);
    }
}

int minimum(int diff[][2], int n) {
    int index = -1;
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!diff[i][1] && min > diff[i][0]) {
            min = diff[i][0];
            index = i;
        }
    }
    return index;
}

void sstf(int request[], int head, int n) {
    if (n == 0) {
        return;
    }
    
    int diff[n][2];
    int seekcount = 0;
    int sequence[n + 1];
    
    for (int i = 0; i < n; i++) {
        sequence[i] = head;
        difference(request, head, diff, n);
        int index = minimum(diff, n);
        diff[index][1] = 1;
        
        seekcount += diff[index][0]; 
        head = request[index];
    }
    sequence[n] = head;
    
    printf("Total number of seek operations = %d\n", seekcount);
    printf("Seek sequence is:\n");
    
    for (int i = 0; i <= n; i++) {
        printf("%d\n", sequence[i]);
    }
}

int main() {
    int n = 8;
    int proc[] = { 176, 79, 34, 60, 92, 11, 41, 114 };
    
    int head = 50;
    sstf(proc, head, n);
    
    return 0;
}