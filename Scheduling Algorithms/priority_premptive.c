#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
    int p;
    int BT;
    int FT;
    int TT;
    int WT;
};

int processes[]={0,1,2,3,4};
int AT[]={0,2,4,6,8};
int BT[]={3,6,4,5,2};
int pri[]={5,4,3,2,1};

int ready[10];
int time_c=0;
int gantt[20] = {0};
int top=0;
int gt=0;

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
        if (p[ready[i]].AT <= time_c && p[ready[i]].p < min_pri){
            min_pri = p[ready[i]].p;
            pid = ready[i];
        }
    }
    return pid;
}

void pr_preempt(){
    while (1){
        if(time_c > 21)
            break;

// insert new process into ready queue
        for(int i=0;i<5;i++){
            if(time_c == p[i].AT)
                insert_ready(p[i].id);
        }

// find out the process with highest priority from read queue
        int hi_id = high_priority();
        if (hi_id != -1)
            delete_ready(hi_id);

        gantt[time_c] = hi_id;
        if (hi_id != -1)
            p[hi_id].burstRemaining--;

        if (p[hi_id].burstRemaining == 0) {
                p[hi_id].FT = time_c+1; // Update finish time
            }

        time_c++;
        if (hi_id != -1)
            insert_ready(hi_id);
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
    for (int i = 0; i < 4; i++){
        printf("%d %2d %2d %2d\n", p[i].id, p[i].AT, p[i].burstRemaining, p[i].p);
    }

    pr_preempt();

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
