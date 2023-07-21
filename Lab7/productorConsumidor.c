#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int counter = 0;
int item_produced = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;

    while (1) {
        pthread_mutex_lock(&mutex);
        while (counter == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }

        item = item_produced;
        buffer[counter] = item;
        printf("Producer produced item: %d\n", item);
        counter++;
        item_produced++;

        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;

    while (1) {
        pthread_mutex_lock(&mutex);
        while (counter == 0) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }

        item = buffer[counter - 1];
        printf("Consumer consumed item: %d\n", item);
        counter--;

        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
