#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t sema1, sema2;
pthread_mutexattr_t semattr1, semattr2;

void *tarea1(void *arg){
        while(1){
        pthread_mutex_lock(&sema1);
        printf("En tarea 1\n");
        pthread_mutex_unlock(&sema2);
        }
}
void *tarea2(void *arg){
        while(1){
        pthread_mutex_lock(&sema2);
        printf("En tarea 2\n");
        pthread_mutex_unlock(&sema1);
        }
}

int main(){
        pthread_t tid1, tid2;
        pthread_attr_t attr;
        pthread_mutexattr_init(&semattr1);
        pthread_mutexattr_init(&semattr2);

        if(pthread_mutex_init(&sema1, &semattr1)==-1){
                  perror("El semaforo 1 no ha podido inicializarse\n");
                  exit(1);
}
        if(pthread_mutex_init(&sema2, &semattr2)==-1){
                  perror("El semaforo 2 no ha podido inicializarse\n");
                  exit(1);
}

        if(pthread_attr_init(&attr)==-1){
                perror("Error: inicialisacion de atributos de thread\n");
                exit(1);
}
         if(pthread_create(&tid1,&attr,tarea1,NULL)==-1){
                perror("Error en la creacion del hilo 1\n");
                exit(1);
}
         if(pthread_create(&tid2,&attr,tarea2,NULL)==-1){
                perror("Error en la creacion del hilo 2\n");
                exit(1);
}
     sleep(1);
     printf("salida del hilo principal \n");
     exit(0);
}

 

