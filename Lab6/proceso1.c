#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

       key_t clave;
       int id_Memoria;
       int *memoria = NULL;
       int i,j;

       clave = ftok ("/bin/ls", 33);
       if (clave == -1){
               printf("No consigo clave para memoria compartida\n");
}
id_Memoria = shmget (clave, sizeof(int)*100, 0777 | IPC_CREAT);
if (id_Memoria == -1){
        printf("No consigo Id para memoria compartida\n");
}
memoria = (int *)shmat (id_Memoria, (char *)0, 0);
if (memoria == NULL){
        printf("No consigo memoria compartida\n");
}
       for (i=0; i<10; i++){
               for (j=0; j<100; j++){
                       memoria[j] = i;
}
       printf("Escrito %d\n",i);
       sleep (1);
}
      shmdt ((char *)memoria);
      shmctl (id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
return 0;
}
