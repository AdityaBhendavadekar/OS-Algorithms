#include<stdio.h>
#include<stdlib.h>

void sort(int arr[], int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i]<arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int findNearest(int arr[], int head, int size){
    int index;
    for(int i=0;i<size;i++){
        if(head<arr[i]){
            index = i;
            break;
        }
    }

}

void scan(int arr[], int head, int size){
    int seek_count=0;
    int distance;
    int current, nearest;
    int sequence[size];
    int count =0;

    sort(arr, size);

    int index = findNearest(arr, head, size);
    nearest = arr[index];
    printf("Nearest: %d \n",nearest);

// for right side.
    for(int i=index;i<size;i++){
        current = arr[i];
        printf(" %d ", current);
        sequence[count++];
        distance = abs(current-head);
        seek_count +=distance;
        head = current;
    }

//for remaining left side
    // if(index>0){
    //     for(int i=index-1;i>=0;i--){
    //         current = arr[i];
    //         sequence[count++];
    //         distance = abs(current-head);
    //         seek_count += distance;
    //         head = current;
    //     }
    // }

    printf(" %d ", seek_count);
    printf("\nSequence: ");
    for(int i=0;i<size;i++){
        printf(" %d ", sequence[i]);
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

    scan(arr, head, n);

    return 0;
}