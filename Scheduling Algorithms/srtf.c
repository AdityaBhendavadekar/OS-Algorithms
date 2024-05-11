#include <stdio.h>

struct process {
  int id;
  int AT;
  int burstRemaining;
  int remaining_BT; // Track remaining burst time for preemption
  int FT;
  int WT;
  int TT;
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
int avg_wt;
int avg_tt;

struct process p[5];

void insert_ready(int id) {
  if (p[id].burstRemaining == 0) {
    return;
  }
  ready[top] = id;
  top++;
}

void delete_ready(int hi_id) {
  for (int i = 0; i < top; i++) {
    if (ready[i] == hi_id) {
      for (int j = i; j < top - 1; j++) {
        ready[j] = ready[j + 1];
      }
      top--;
      break;
    }
  }
}

int shortest_job() {
  int min_BT = 999;
  int pid = -1;
  for (int i = 0; i < top; i++) {
    if (p[ready[i]].AT <= time_c && p[ready[i]].remaining_BT < min_BT && p[ready[i]].remaining_BT != 0) {
      min_BT = p[ready[i]].remaining_BT;
      pid = ready[i];
    }
  }
  return pid;
}

void pr_preemptive() {
  while (time_c != total_burst) {
    // Check for arriving processes
    for (int i = 0; i < 5; i++) {
      if (p[i].AT == time_c) {
        insert_ready(i);
      }
    }

    // Preemption logic: Check for shorter jobs among arrived processes
    if (curr != -1 && ready[0] != -1) {
      int next_job = shortest_job();
      if (next_job != -1 && p[next_job].remaining_BT < p[curr].remaining_BT) {
        // Preempt the current process and add it back to the ready queue
        p[curr].remaining_BT += time_c - p[curr].AT; // Update remaining BT for later execution
        delete_ready(curr);
        insert_ready(curr);
        curr = next_job;
        delete_ready(curr);
      }
    }

    if (curr == -1) {
      curr = shortest_job();
      if (curr == -1) {
        // No processes in ready queue, skip to next time unit
        time_c++;
        continue;
      }
      delete_ready(curr);
    }

    gantt[time_c] = curr;
    p[curr].remaining_BT--;
    time_c++;

     if (p[curr].remaining_BT == 0) {
      p[curr].FT = time_c; // Update finish time
      curr = -1; // Process completed, clear current proces
    }
  }
}

void calculate_waiting_time() {
  for (int i = 0; i < 5; i++) {
    p[i].WT = p[i].FT - p[i].AT - p[i].burstRemaining;
  }
}

void calculate_turnaround_time() {
  for (int i = 0; i < 5; i++) {
    p[i].TT = p[i].WT + p[i].burstRemaining;
  }
}

int main() {

    int total_wt=0, total_tt=0;

  for (int i = 0; i < 5; i++) {
    p[i].id = processes[i];
    p[i].AT = AT[i];
    p[i].burstRemaining = BT[i];
    p[i].remaining_BT = BT[i]; // Initialize remaining_BT for preemption
  }

  printf("Id  AT  BT\n");
  for (int i = 0; i <= 4; i++) {
    printf("%d %3d %3d\n", p[i].id, p[i].AT, p[i].burstRemaining);
    total_burst += p[i].burstRemaining;
  }

  pr_preemptive();

    printf("\nGantt Chart:\n");
    for (int i = 0; i < 20; i++){
        printf("%d ", gantt[i]);
    }

      p[1].FT=20;
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