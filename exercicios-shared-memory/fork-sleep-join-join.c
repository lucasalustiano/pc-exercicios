#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *daugtherExec(void *threadid) {
    long tid = (long)threadid;
    int tempoDeDormida = rand() % 5;
    printf("A Thread filha número %ld está prestes a mimir por %d segundos!\n", (tid + 1), tempoDeDormida);

    sleep(tempoDeDormida);

    return NULL;
}

int main(int argc, char const *argv[]) {
    int num_threads;

    printf("\nQuantas threads deverão ser criadas? ");
    scanf("%i", &num_threads);
    printf("------------------------------------------------------------\n");

    pthread_t threads[num_threads];

    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, daugtherExec, (void *)i);
        pthread_join(threads[i], NULL);
    }

    printf("------------------------------------------------------------\n");
    printf("\nn: %i\n", num_threads);

    pthread_exit(NULL);
}