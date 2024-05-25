#include<stdio.h>
#include<stdlib.h>

void FCFS(int arr[], int head, int size){
    int curr_track;
    int distance, seek_time=0;

    for(int i=0;i<size; i++){
        curr_track = arr[i];
        distance = abs(curr_track - head);
        seek_time +=distance;
        head = curr_track;
    }

    printf("Total Seek Time is: %d", seek_time);
}

int main(){
    int n, head;
    printf("No. of tracks: ");
    scanf("%d", &n);
    int arr[n];

    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    printf("Head position: ");
    scanf("%d", &head);

    FCFS(arr, head, n);

    printf("\nSequence: ");
    for(int i=0;i<n;i++)
        printf(" %d ", arr[i]);

    return 0;
}