#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *funcion01(void *arg){
        int i;
        for(i=0;i<20;i++){
        printf(".");
        fflush(stdout);
        sleep(1);
        }
        return NULL;
}
void *funcion02(void *arg){
        int i;
        for(i=0;i<20;i++){
        printf("o");
        fflush(stdout);
        sleep(1);
        }
        return NULL;
}
void *funcion03(void *arg){
        int i;
        for(i=0;i<20;i++){
        printf("+");
        fflush(stdout);
        sleep(1);
        }
        return NULL;
}
int main(int argc, char *argv[]){
        pthread_t hilo1, hilo2, hilo3;
        int i;
        printf("Creando hilos...\n");
        if(pthread_create(&hilo1,NULL,funcion01,NULL)){
        printf("Error al crear Hilo 1");
        abort();
        }
        if(pthread_create(&hilo1,NULL,funcion02,NULL)){
        printf("Error al crear Hilo 2");
        abort();
        }
        if(pthread_create(&hilo1,NULL,funcion03,NULL)){
        printf("Error al crear Hilo 3");
        abort();
        }
        for(i=0;i<20;i++){
        printf("x");
        fflush(stdout);
        sleep(3);
        }
        exit(0);
}
