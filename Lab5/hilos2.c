#include <pthread.h>
#include <stdio.h>

int main(){
    void *mifuncion(void *arg);
    pthread_t tid;
    int misargs[2];
    printf("Creando hilo...\n");
    fflush(stdout);
    misargs[0]=-5;
    misargs[1]=-6;
    
    pthread_create(&tid,NULL,mifuncion,(void *)misargs);
    printf("Hilo creado. Esperando a que termine...\n");
    fflush(stdout);
    pthread_join(tid,NULL);
    printf("Hilo finalizado...\n");
    fflush(stdout);
}
void *mifuncion(void *arg){
    printf("Soy mifuncion...\n");
    printf("Argumento 1: %d. Argumento 2: %d\n",
    ((int)(arg)),*((int*)(arg)+1));
    fflush(stdout);
}
