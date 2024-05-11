#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
    int BT;
    int p;
    int FT;
    int WT;
    int TT;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,8,6,4};
int BT[]={3,6,4,5,2};
int pri[]={5,4,3,2,1};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;
int total_burst;

struct process p[4];

void insert_ready(int id){
    if (p[id].burstRemaining == 0)
        return;
    ready[top]= id;
    top++;
}

void delete_ready(int hi_id){
    for (int i = 0; i < top; i++){
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

int high_priority(){
    int min_pri = 999; 
    int pid = -1; 
    for(int i=0;i<top;i++){
        if (p[ready[i]].AT <= time_c && p[ready[i]].p < min_pri && p[ready[i]].burstRemaining!=0){
            min_pri = p[ready[i]].p;
            pid = ready[i];
        }
    }
    return pid;
}

void pr_nonpreempt(){
    while (1){
        if(time_c == total_burst)
            break;

        for(int i=0;i<5;i++){
            if(time_c == p[i].AT && p[i].burstRemaining!=0){
                insert_ready(p[i].id);
            }
        }

        int hi_id = high_priority();

        for (int i = p[hi_id].burstRemaining; i > 0; i--)
        {
            gantt[time_c]=hi_id;
            time_c++;
            p[hi_id].burstRemaining--;

            if (p[hi_id].burstRemaining == 0) {
                p[hi_id].FT = time_c;
            }
         
            for(int i=0;i<5;i++){
                if(time_c == p[i].AT && p[i].burstRemaining!=0){
                    insert_ready(p[i].id);
                }
            }
        }
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
        p[i].p = pri[i];
        p[i].BT = BT[i];
    }

    printf("Id  AT  BT  Pri\n");
    for (int i = 0; i <= 4; i++){
        printf("%d %2d %2d %2d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].p);
        total_burst+=p[i].burstRemaining;
    }

    pr_nonpreempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

     calculate_turnaround_time();
    calculate_waiting_time();

    printf("\nId  AT  BT  FT  TT  WT \n");
    
    for (int i = 0; i <= 4; i++) {
        printf("%d %3d %3d %3d %3d %3d\n", p[i].id, p[i].AT, p[i].BT, p[i].FT, p[i].TT, p[i].WT);
        total_wt+=p[i].WT;
        total_tt += p[i].TT;
  }

  printf("Average waiting time: %d\n", total_wt/5);
  printf("Average turnaround time: %d\n", total_tt/5);

    return 0;
}
