#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

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
        int i=0;
        clave = ftok("/bin/ls",33);
        if(clave==(key_t)-1){
                  printf("No se puede conseguir la clave del semaforo\n");
}
idSemaforo=semget(clave,10,0600|IPC_CREAT);
if(idSemaforo==-1){
        printf("No se puede crear el Semaforo\n");
}
operacion.sem_num = 0;
operacion.sem_op = 1;
operacion.sem_flg = 0;
for(i=0;i<10;i++){
printf("**levantando el semaforo**\n");
semop(idSemaforo,&operacion,1);
sleep(1);
}
return 0;
}
