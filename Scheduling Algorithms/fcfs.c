#include<stdio.h>

struct process
{
    int id;
    int AT;
    int BT;
    int FT;
    int TT;
    int WT;
    int burstRemaining;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,4,6,8};
int BT[]={3,6,4,5,2};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;
int total_burst;
int rear=-1, front=-1;
int curr=-1;

struct process p[4];

void enque(int q[], int *f, int *r, int p){

    if((*f) ==-1 && (*r) == -1 ){
        (*f)=0;
        (*r)=0;
    }

    q[(*r)] = p;
    (*r)++;

}

int deque(int q[], int *f, int *r){

    if((*f) > (*r) ){
        printf("Empty Queue.");
        return -1;
    }

    return q[(*f)++];
}

void fcfs(){

    while (time_c!=total_burst){

        for (int i = 0; i < 5; i++)
        {
            if( p[i].AT == time_c ){
                enque(ready, &front, &rear, p[i].id);
            }
        }

        if(p[curr].burstRemaining == 0 || curr==-1){
            curr = deque(ready, &front, &rear);
        }

        gantt[time_c] = curr;
        p[curr].burstRemaining--;

        if (p[curr].burstRemaining == 0) {
            p[curr].FT = time_c + 1; // Add 1 to account for the current time unit
        }

        time_c++;
    }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].BT;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].BT;
  }
}

int main(){

    int total_wt=0 ,total_tt=0;

    for(int i=0;i<5;i++){
        p[i].id=processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
        p[i].BT = BT[i];
    }

    printf("Id  AT  BT \n");
    for (int i = 0; i <= 4; i++){
        printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].BT);
        total_burst+=p[i].BT;
    }

    fcfs();

    printf("\nReady Queue:\n");
    for (int i = 0; i < 5; i++){
        printf("%d ", ready[i]);
    }

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

     calculate_turnaround_time();
    calculate_waiting_time();

      printf("\nId  AT  BT  FT  TT  WT \n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].FT, p[i].TT, p[i].WT);
    total_wt+=p[i].WT;
    total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);

    return 0;
}
