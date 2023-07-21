#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMANO_BUFFER 1000

int buffer[TAMANO_BUFFER];
// pthread_mutex_t mutexBuffer;

void *funcionThread(void *arg) {
    int i;
    int elementoDist = 0;
    while (1) {
        // pthread_mutex_lock(&mutexBuffer);
        for (i = 0; i < TAMANO_BUFFER; i++) {
            if (buffer[0] != buffer[i]) {
                elementoDist = 1;
                break;
            }
        }
        if (elementoDist) {
            printf("Hijo: Error. Elementos distintos a buffer\n");
        } else {
            printf("Hijo: correcto %d\n", elementoDist);
        }
  //       pthread_mutex_unlock(&mutexBuffer);
    }
}

int main() {
    pthread_t idHilo;
    int error;
    int contador;
    int i;
   // pthread_mutex_init(&mutexBuffer, NULL);
    error = pthread_create(&idHilo, NULL, funcionThread, NULL);
    if (error != 0) {
        perror("No se puede crear hilo...");
        exit(1);
    }

    while (1) {
       // pthread_mutex_lock(&mutexBuffer);
        for (i = 0; i < TAMANO_BUFFER; i++) {
            buffer[i] = contador;
        }
        printf("Hilo principal: contador en %d\n", contador);
       // pthread_mutex_unlock(&mutexBuffer);
        contador++;
    }
    return 0;
}

