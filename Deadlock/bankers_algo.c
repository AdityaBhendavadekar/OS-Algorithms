#include<stdio.h>

int process[5]={0,1,2,3,4};
int allocated[5][3]={
    {0,1,0},
    {2,0,0},
    {3,0,2},
    {2,1,2},
    {0,0,2}
};

int max[5][3]={
    {7,5,3},
    {3,2,2},
    {9,0,2},
    {2,2,2},
    {4,3,3}
};
int work[3]={3,3,2};
int need[5][3];
int finish[5];
int squence[5];
int ind = 0;

void bankers(int m, int n){
    for(int s=0;s<n;s++){
        for(int i=0;i<m;i++){

            if(finish[i]==0){
                if(need[i][0] <= work[0] && need[i][1] <= work[1] && need[i][2] <= work[2]){
                    finish[i] = 1;
                    squence[ind++] = i;
                    for(int k=0;k<n;k++){
                        work[k] =work[k]+allocated[i][k];
                    }
                }
            }
        }
    }
}

int main(){
    int m = 5;
    int n = 3;
    for (int i = 0; i < m; i++){
        finish[i]=0;
    }
    
    // finding need matrix
    for (int i = 0; i < m; i++){
        for(int j=0;j<n;j++){
            need[i][j]=max[i][j] - allocated[i][j];
        }
    }

    bankers( m, n);

    int flag=0;
    // finding if all processes executed succefully by checking flag
    for (int i = 0; i < m; i++){
        if(finish[i] == 0){
            flag = 1;
            break;
        }
    }
    
    if(flag==0){
        printf("Safe state sequence for processes is: \n");
        for (int i = 0; i < m; i++){
            printf("%d -> ", squence[i]);
        }
    }
    else
        printf("System is not safe.");
    
    return 0;
}