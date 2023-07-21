#include <unistd.h>
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

    long tipo_lectura = 1;
    long tipo_actual = tipo_lectura;

    while (1) {
        msgrcv(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), tipo_actual, 0);

        printf("Recibiendo mensaje tipo %ld:\n", tipo_actual);
        printf("Dato_Numerico = %d\n", Un_Mensaje.Dato_Numerico);
        printf("Mensaje = %s\n", Un_Mensaje.Mensaje);

        tipo_actual = (tipo_actual % 3) + 1;

        if (msgsnd(Id_Cola_Mensajes, (struct msgbuf *)&Un_Mensaje, sizeof(Un_Mensaje.Dato_Numerico) + sizeof(Un_Mensaje.Mensaje), IPC_NOWAIT) == -1) {
            printf("Error al enviar el mensaje\n");
            return 1;
        }
    }

    return 0;
}
