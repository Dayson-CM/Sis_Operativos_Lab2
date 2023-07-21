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
    key_t clave1;
    int Id_Cola_Mensajes;
    Mi_Tipo_Mensaje Un_Mensaje;

    clave1 = ftok("/bin/ls", 33);
    if (clave1 == (key_t)-1) {
        printf("Error al obtener clave para cola de mensajes\n");
        return 1;
    }

    Id_Cola_Mensajes = msgget(clave1, 0600 | IPC_CREAT);
    if (Id_Cola_Mensajes == -1) {
        printf("Error al obtener ID para la cola de mensajes\n");
        return 1;
    }

    Un_Mensaje.Id_Mensaje = 1;
    Un_Mensaje.Dato_Numerico = 29;
    strcpy(Un_Mensaje.Mensaje, "Hola");

    if (msgsnd(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT) == -1) {
        printf("Error al enviar el mensaje\n");
        return 1;
    }

    if (msgrcv(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), 2, 0) == -1) {
        printf("Error al recibir el mensaje\n");
        return 1;
    }

    printf("Recibido mensaje tipo 2\n");
    printf("Dato_Numerico = %d\n", Un_Mensaje.Dato_Numerico);
    printf("Mensaje = %s\n", Un_Mensaje.Mensaje);

    if (msgctl(Id_Cola_Mensajes, IPC_RMID, NULL) == -1) {
        printf("Error al eliminar la cola de mensajes\n");
        return 1;
    }

    return 0;
}

