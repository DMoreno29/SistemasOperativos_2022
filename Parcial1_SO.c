#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

/* Funcion para pasar a mayusculas */
void conUpper(char *cad) {
    int lenght = strlen(cad);
    for (int indice = 0; indice < lenght; indice++)
        cad[indice] = toupper(cad[indice]);
}

int main()
{
    /* Tuberia 1 */
    int field1[2];
    if (pipe(field1) < 0)
    {
        printf("Falló la creación de la tuberia 1");
    }
    
    /* Tuberia 2 */
    int field2[2];
    if (pipe(field2) < 0)
    {
        printf("Falló la creacion de la tuberia 2");
    }

    /* Crear proceso hijo*/
    int pid = fork();
    if (pid == 0)
    {
        while(1)
        {
            /* Limpiar buffer*/
            char wRecibida[100];
            memset(wRecibida, 0, sizeof(wRecibida));

            /* Hijo lee de tuberia 1 */
            read(field1[0], wRecibida, sizeof(wRecibida));
            printf("Hijo recibe: %s\n", wRecibida);
            
            /* Pasa a mayúscula */
            conUpper(wRecibida);

            /* Hijo escribe en tuberia 2 */
            write(field2[1], wRecibida, sizeof(wRecibida));
        }
    }
    else
    {
        while(1)
        {
            printf("Ingrese una cadena de texto: ");

            /* Cadena de texto */
            char sEntrada[100];
            memset(sEntrada, 0, sizeof(sEntrada));
            scanf("%[^\n]%*c", sEntrada);

            /*Padre escribe en tuberia 1 */
            write(field1[1], sEntrada, sizeof(sEntrada));

            /* Limpiamos buffer */
            char wMayus[100];
            memset(wMayus, 0, sizeof(wMayus));
            
            /* Padre lee de tuberia 2 */
            read(field2[0], wMayus, sizeof(wMayus));
            printf("Padre recibe de nuevo: %s\n", wMayus);
        }
    }
    close(field1[0]);
    close(field1[1]);
    close(field2[0]);
    close(field2[1]);
    return 0;
}
