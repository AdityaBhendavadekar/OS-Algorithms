#include<stdio.h>

struct process
{
    int id;
    int AT;
    int burstRemaining;
};

int processes[] = {0, 1, 2, 3, 4};
int AT[] = {0, 2, 4, 6, 8};
int BT[] = {3, 6, 4, 5, 2};

int ready[10];
int time_c = 0;
int gantt[20] = {0};
int top = 0;
int gt = 0;
int total_burst;
int curr = -1;
int iterate = 0;
int ct = 0;
int rd_pc = 0;

struct process p[4];

void insert_ready(int id) {
    if (p[id].burstRemaining == 0)
        return;
    ready[top] = id;
    top++;
}

void delete_ready(int hi_id) {
    for (int i = 0; i < top; i++) {
        if (ready[i] == hi_id) {
            for (int j = i; j < top - 1; j++)
                ready[j] = ready[j + 1];
            top--;
            break;
        }
    }
}

void pr_nonpreempt() {
    while (time_c != total_burst) {

        for (int i = 0; i < 5; i++) {
            if (p[i].AT == time_c) {
                insert_ready(i);
                rd_pc++;
            }
        }

        if (ct >= 2 || p[curr].burstRemaining <= 0) {
            int next_process = iterate % rd_pc;
            curr = ready[next_process];
            iterate++;
            ct = 0;
        }

        gantt[time_c] = curr;

         if (p[curr].burstRemaining <= 0 && curr!=-1) {
            delete_ready(curr);
            rd_pc--;
        }
    
        p[curr].burstRemaining--;
        ct++;
        time_c++;
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        p[i].id = processes[i];
        p[i].AT = AT[i];
        p[i].burstRemaining = BT[i];
    }

    printf("Id  AT  BT\n");
    for (int i = 0; i < 5; i++) {
        printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining);
        total_burst += p[i].burstRemaining;
    }

    pr_nonpreempt();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < total_burst; i++) {
        printf("%d ", gantt[i]);
    }

    return 0;
}
