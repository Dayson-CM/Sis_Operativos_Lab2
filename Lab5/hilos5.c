#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex; // Declaración del mutex

void *funcion01(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex); // Adquirir el cerrojo del mutex
        printf(".");
        fflush(stdout);
        pthread_mutex_unlock(&mutex); // Liberar el cerrojo del mutex
        sleep(1);
    }
    return NULL;
}

void *funcion02(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex); // Adquirir el cerrojo del mutex
        printf("o");
        fflush(stdout);
        pthread_mutex_unlock(&mutex); // Liberar el cerrojo del mutex
        sleep(1);
    }
    return NULL;
}

void *funcion03(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex); // Adquirir el cerrojo del mutex
        printf("+");
        fflush(stdout);
        pthread_mutex_unlock(&mutex); // Liberar el cerrojo del mutex
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t hilo1, hilo2, hilo3;
    int i;
    printf("Creando hilos...\n");
    pthread_mutex_init(&mutex, NULL); // Inicializar el mutex

    if (pthread_create(&hilo1, NULL, funcion01, NULL)) {
        printf("Error al crear el Hilo 1");
        abort();
    }
    if (pthread_create(&hilo2, NULL, funcion02, NULL)) {
        printf("Error al crear el Hilo 2");
        abort();
    }
    if (pthread_create(&hilo3, NULL, funcion03, NULL)) {
        printf("Error al crear el Hilo 3");
        abort();
    }

    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex); // Adquirir el cerrojo del mutex
        printf("x");
        fflush(stdout);
        pthread_mutex_unlock(&mutex); // Liberar el cerrojo del mutex
        sleep(3);
    }

    pthread_mutex_destroy(&mutex); // Destruir el mutex
    exit(0);
}
