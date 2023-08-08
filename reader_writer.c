#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t rw_mutex, mutex;
int data = 0;
int reader_count = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {
       
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader %d reads data: %d\n", reader_id, data);

        
        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        
        usleep(rand() % 1000000);
    }
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {
        
        sem_wait(&rw_mutex);

        data = rand() % 100;
        printf("Writer %d writes data: %d\n", writer_id, data);

        sem_post(&rw_mutex);

        usleep(rand() % 1000000);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

   
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

  
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
