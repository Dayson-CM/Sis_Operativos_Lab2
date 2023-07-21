#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

typedef struct Mi_Tipo_Mensaje {
    long Id_Mensaje;
    int Dato_Numerico;
    char Mensaje[10];
} Mi_Tipo_Mensaje;

int main() {
    key_t Clave1;
    int Id_Cola_Mensajes;
    Mi_Tipo_Mensaje Un_Mensaje;

    Clave1 = ftok("/bin/ls", 33);
    if (Clave1 == (key_t)-1) {
        printf("Error al obtener clave para cola de mensajes\n");
        return 1;
    }

    Id_Cola_Mensajes = msgget(Clave1, 0600 | IPC_CREAT);
    if (Id_Cola_Mensajes == -1) {
        printf("Error al obtener ID para la cola de mensajes\n");
        return 1;
    }

    msgrcv(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), 1, 0);

    printf("Recibiendo mensaje tipo 1:\n");
    printf("Dato_Numerico = %d\n", Un_Mensaje.Dato_Numerico);
    printf("Mensaje = %s\n", Un_Mensaje.Mensaje);

    Un_Mensaje.Id_Mensaje = 2;
    Un_Mensaje.Dato_Numerico = 13;
    strcpy(Un_Mensaje.Mensaje, "Adios:-)");

    if (msgsnd(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT) == -1) {
        printf("Error al enviar el mensaje\n");
        return 1;
    }

    return 0;
}

