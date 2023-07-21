#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

union semun{
int val;
struct semid_ds *buf;
unsigned short int *array;
struct seminfo *_buf;
};

int main(){
        key_t clave;
        int idSemaforo;
        struct sembuf operacion;
        union semun arg;
        int i=0;
        clave = ftok("/bin/ls",33);
        if(clave==(key_t)-1){
                  printf("No se puede conseguir la clave de semaforo \n ");
}

idSemaforo=semget(clave,10,0600|IPC_CREAT);
if(idSemaforo==-1){
        printf("No se puede crear el semaforo \n");
}
arg.val = 0;
semctl(idSemaforo,0,SETVAL,&arg);
operacion.sem_num=0;
operacion.sem_op= -1;
operacion.sem_flg = 0;

while(1){
printf("Esperando semaforo.......%d\n",i);
semop(idSemaforo,&operacion,1);
printf("...........Saliendo del semaforo %d\n",i);
i++;
}
return 0;
}
