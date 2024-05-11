#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
sem_t mutex, writeblock;
int data = 0, rcount = 0;
void *reader(void *arg) {
int f;
f = *((int *)arg);
sem_wait(&mutex);
rcount++;
if (rcount == 1) {
sem_wait(&writeblock);
}
sem_post(&mutex);
printf("Reader %d is reading data: %d\n", f, data);
sleep(2);
sem_wait(&mutex);
rcount--;
if (rcount == 0) {
sem_post(&writeblock);
}
sem_post(&mutex);
return NULL;
}
void *writer(void *arg) {
int f;
f = *((int *)arg);
sem_wait(&writeblock);
data++;
printf("Data Written By The Writer: %d\n", data);
sleep(1);
sem_post(&writeblock);
return NULL;
}
int main() {
int i;
pthread_t rtid[3], wtid[3];
sem_init(&mutex, 0, 1);
sem_init(&writeblock, 0, 1);
while (1) {
for (i = 0; i < 3; i++) {
pthread_create(&wtid[i], NULL, writer, &i);
pthread_create(&rtid[i], NULL, reader, &i);
}
for (i = 0; i < 3; i++) {
pthread_join(wtid[i], NULL);
pthread_join(rtid[i], NULL);
}
sleep(5); // Delay for 5 seconds before running the loop again
printf("\n\n");
}
return 0;
}
