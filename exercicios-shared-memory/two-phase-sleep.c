#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, locker;
int threadsCount, threadsTotal;
int listaTempoDeDormida[INT_MAX];

void *daugtherExec(void *threadid) {
    sem_wait(&mutex);
    
    long tid = (long)threadid;
    int tempoDeDormidaFase1 = rand() % 5;
    printf("A Thread filha número %ld está prestes a mimir por %d segundos!\n", (tid + 1), tempoDeDormidaFase1);
    sleep(tempoDeDormidaFase1);
    threadsCount--;

    int tempoDeDormidaParaFase2 = rand() % 10;
    listaTempoDeDormida[tid] = tempoDeDormidaParaFase2;
    printf("A Thread filha número %ld escolheu %d segundos!\n\n", (tid + 1), tempoDeDormidaParaFase2);
    
    sem_post(&mutex);

    if (threadsCount != 0) {  // inicio da segunda fase
      sem_wait(&locker);      // n - 1 threads tão bloqueadas aqui
    } 
    
    if (tid == 0) {
      //primeira thread
      int tempoDeDormida = listaTempoDeDormida[threadsTotal - 1];
      printf("A Thread filha número %ld está prestes a mimir por %d segundos!\n", (tid + 1), tempoDeDormida);
      sleep(tempoDeDormida);
    } else {
      //outras threads
      int tempoDeDormida = listaTempoDeDormida[tid - 1];
      printf("A Thread filha número %ld está prestes a mimir por %d segundos!\n", (tid + 1), tempoDeDormida);
      sleep(tempoDeDormida);
    }

    sem_post(&locker);

    return NULL;
}

int main(int argc, char const *argv[]) {
    int num_threads;

    printf("\nQuantas threads deverão ser criadas? ");
    scanf("%i", &num_threads);
    printf("------------------------------------------------------------\n");

    sem_init(&mutex, 0, 1);
    sem_init(&locker, 0, 0);
    threadsCount = num_threads;
    threadsTotal = num_threads;
    int listaTempoDeDormida[num_threads];
    pthread_t threads[num_threads];

    for (long i = 0; i < num_threads; i++) {
      pthread_create(&threads[i], NULL, daugtherExec, (void *)i);
    }

    sem_close(&mutex);
    sem_close(&locker);
    pthread_exit(NULL);
}