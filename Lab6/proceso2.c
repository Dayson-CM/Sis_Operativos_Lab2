#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
      key_t clave;
      int id_Memoria;
      int *Memoria = NULL;
      int i,j;

      clave = ftok ("/bin/ls", 33);
      if (clave == -1){
             printf("No consigo clave para la memoria compartida\n");
}
id_Memoria = shmget (clave, sizeof(int)*100, 0777);
if (id_Memoria == -1){
        printf("No consigo Id para memoria compartida\n");
}
Memoria = (int *)shmat (id_Memoria, (char *)0, 0);
if (Memoria == NULL){
       printf("No consigo memoria compartida\n");
}
for (i=0; 1<10; i++){
        printf("Leido %d\n", Memoria [0]);
        sleep (1);
}
if (id_Memoria != -1){
         shmdt ((char *)Memoria);
}
return 0;
}
