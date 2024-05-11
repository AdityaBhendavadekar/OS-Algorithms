#include<stdio.h>

int partitions, processes;


void firstFit(int memory[partitions],int pSize[processes], int allo[partitions], int unallo[partitions]){
    int ind1=0, ind2=0;
    
    for(int i=0;i<processes;i++){
        int flag = 0;
        for(int j=0;j<partitions;j++){
            
            if(pSize[i]<=memory[j]){
                memory[j] = memory[j] - pSize[i];
                allo[ind1++] = i;
                flag=1;
                break;
            }
        }
        if(flag==0){
            unallo[ind2++]=i;
        }
    }

    printf("Processes allocated memory are: \n");
    for(int i=0;i<ind1;i++){
        printf(" P%d ", allo[i]);
    }

    printf("\nProcesses remain unallocated memory are:");
    for(int i=0;i<ind2;i++){
        printf(" P%d ", unallo[i]);
    }
    printf("\n");
}

void nextFit(int memory[partitions], int pSize[processes], int allo[partitions], int unallo[partitions]) {
    int ind1 = 0, ind2 = 0;
    int n = 0, m = 0;
    int lastAllocated = 0; 

    for (int i = 0; i < processes; i++) {
        int start = lastAllocated; // Start searching for the next fit from the last allocated partition
        while (n <= m) {
            if (memory[m] >= pSize[i]) {
                allo[ind1++] = i;
                memory[m] -= pSize[i];
                lastAllocated = m; // Update last allocated partition
                break; // Exit the loop once allocation is done
            }
            m = (m + 1) % partitions;
            // If we have searched all partitions and didn't find a fit, break the loop
            if (m == start) 
                break;
        }
    }

    printf("Processes allocated memory are: \n");
    for (int i = 0; i < ind1; i++) {
        printf(" P%d ", allo[i]);
    }
    printf("\n");
}



void bestFit(int memory[], int pSize[], int allo[], int unallo[]) {
    int ind1 = 0, ind2 = 0;

    for (int i = 0; i < processes; i++) {
        int minSub = 1000; // Initialize the minimum difference to a very large value
        int minIndex = -1; // Initialize the index of the partition with the minimum difference
        
        for (int j = 0; j < partitions; j++) {
            if (memory[j] >= pSize[i]) { // Check if the partition has enough space for the process
                int sub = memory[j] - pSize[i]; // Calculate the difference in memory size
                
                if (sub < minSub) { // Check if this partition has the minimum difference so far
                    minSub = sub;
                    minIndex = j;
                }
            }
        }

        if (minIndex != -1) { // If a suitable partition was found
            memory[minIndex] -= pSize[i]; // Allocate memory for the process
            allo[ind1++] = i; // Update the allocated processes array
        } else {
            unallo[ind2++] = i; // Store unallocated processes
        }
    }

    printf("Processes allocated memory are: \n");
    for (int i = 0; i < ind1; i++) {
        printf(" P%d ", allo[i]);
    }
    printf("\n");

    printf("Unallocated processes are: \n");
    for (int i = 0; i < ind2; i++) {
        printf(" P%d ", unallo[i]);
    }
    printf("\n");
}

void worstFit(int memory[], int pSize[], int allo[], int unallo[]) {
    int ind1=0, ind2=0;
    int max=0;

    for(int i=0;i<processes;i++){
        max=0;
        for(int j=0;j<partitions;j++){
           
            if(memory[j]>memory[max]){
                max = j;
            }
        }
        if(memory[max]>=pSize[i]){
            allo[ind1++] = i;
            memory[max] -=pSize[i];
        }else{
            unallo[ind2++] = i;
        }
    }

    printf("\nMemory allocated to following processes: \n");
    for (int i = 0; i < ind1; i++)
    {
        printf("P%d ", allo[i]);
    }

    printf("\nMemory not allocated to following processes: \n");
    for (int i = 0; i < ind2; i++)
    {
        printf("P%d ", unallo[i]);
    }
    
    printf("\n");
}

int main(){
    
    printf("Enter no. of partitions: ");
    scanf("%d", &partitions);

    int fM[partitions];
    int nM[partitions];
    int bM[partitions];
    int wM[partitions];


    int ffA[partitions], ffUn[partitions];
    int nfA[partitions], nfUn[partitions];
    int bfA[partitions], bfUn[partitions];
    int wfA[partitions], wfUn[partitions];

    
    printf("Enter size of each partition: ");
    for (int i = 0; i < partitions; i++)
    {
        printf("Partition %d", i+1);
        scanf("%d", &fM[i]);
        nM[i] = fM[i];
        bM[i] = fM[i];
        wM[i] = fM[i];
    }

    printf("Enter no. of processes: ");
    scanf("%d", &processes);
    int pSize[processes];

    printf("Enter size of each process: ");
    for (int i = 0; i < processes; i++)
    {
        printf("Size of process %d", i+1);
        scanf("%d", &pSize[i]);
    }    

    printf("\nFirst Fit Memory Allocation Technique: \n");
    firstFit(fM, pSize, ffA, ffUn);

    printf("\nNext fit Memory Allocation Technique: \n");
    nextFit(nM, pSize, nfA, nfUn);

    printf("\nBest First Memory Allocation Technique: \n");
    bestFit(bM, pSize, bfA, bfUn);

    printf("\nWorst First Memory Allocation Technique: \n");
    worstFit(wM, pSize, wfA, wfUn);

    return 0;
}