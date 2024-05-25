#include<stdio.h>
#include<stdlib.h>

void sort(int arr[], int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i]<arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// what if head is greater than all numbers present in array
int findNearest(int arr[], int head, int size){
    int index;
    for(int i=0;i<size;i++){
        if(head<arr[i]){
            index = i;
            break;
        }
    }
    return index;
}

void cscan(int arr[], int head, int size){
    int current, seek_time =0;
    int sequence[size+1];
    int count=0, distance;

    sort(arr, size);

    int index = findNearest(arr, head, size);

// goto right track
    for(int i=index;i<size;i++){
        current = arr[i];
        sequence[count++]=current;
        distance = abs(current - head);
        seek_time +=distance;
        head = current;
    }

    //go back to zero 
    current = 0;
    sequence[count++] = current;
    distance = abs(current-head);
    seek_time += distance;
    head = current;
    
    // start again from zero
    for(int i=0;i<index;i++){
        current = arr[i];
        sequence[count++] = current;
        distance = abs(current-head);
        seek_time +=distance;
        head = current;
    }

    printf(" Seek Time: %d \nSequence: ",seek_time);
    for(int i=0;i<=size;i++){
        printf(" %d ",sequence[i]);
    }

}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }

    int head;
    scanf("%d", &head);

    cscan(arr, head, n);

    return 0;
}