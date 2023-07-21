#include <stdio.h>
#include <pthread.h>

#define COUNT_LIMIT 20

int count = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *counter1(void *arg) {
    while (count <= COUNT_LIMIT) {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 1) {
            printf("Thread 1: %d\n", count);
            count++;
            pthread_cond_signal(&cond);
        } else {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *counter2(void *arg) {
    while (count <= COUNT_LIMIT) {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 0) {
            printf("Thread 2: %d\n", count);
            count++;
            pthread_cond_signal(&cond);
        } else {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, counter1, NULL);
    pthread_create(&thread2, NULL, counter2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
