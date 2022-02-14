#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
int threadsCount;

void *daugtherExec(void *threadid) {
    sem_wait(&mutex);
    
    long tid = (long)threadid;
    int tempoDeDormida = rand() % 5;
    printf("A Thread filha número %ld está prestes a mimir por %d segundos!\n", (tid + 1), tempoDeDormida);
    sleep(tempoDeDormida);
    threadsCount--;
    
    sem_post(&mutex);
    
    return NULL;
}

int main(int argc, char const *argv[]) {
    int num_threads;

    printf("\nQuantas threads deverão ser criadas? ");
    scanf("%i", &num_threads);
    printf("------------------------------------------------------------\n");

    sem_init(&mutex, 0, 1);
    threadsCount = num_threads;
    pthread_t threads[num_threads];

    for (long i = 0; i < num_threads; i++) {
      pthread_create(&threads[i], NULL, daugtherExec, (void *)i);
    }

    do {
      if (threadsCount == 0) {
        printf("------------------------------------------------------------\n");
        printf("\nn: %i\n", num_threads);
        break;
      }
    } while (1);

    pthread_exit(NULL);
}