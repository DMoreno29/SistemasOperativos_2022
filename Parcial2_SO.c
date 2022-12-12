#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <time.h> 

struct tupla{
    int dir; //Dirección ingresada
    int pag; //Número de página
    int des; //Desplazamiento
};

int main(){
    
    //Declaramos el tamaño del array de structs
    struct tupla obj;
    struct tupla TLB[10];
    int *space = malloc(sizeof(TLB));

    //Indice
    int ind = 0;
    while(1){

        //Tiempo de ejecución
        double tEjec = 0.0;
        clock_t begin = clock();

        //Entrada de texto
        char ingresarDireccion[20];
        printf("Ingrese dirección virtual: ");
        fgets(ingresarDireccion, 20, stdin);
        
        if(ingresarDireccion[0] != 's'){

            //Conversión de memoria
            int dirIngresada = atoi(ingresarDireccion);

            //Válida el TLB
            bool find = false;
            int indTrue = 0;
            for(int i = 0; i < 10; i++){
                if(TLB[i].dir == dirIngresada){
                    find = true;
                    indTrue = i;
                    break;
                }
            }

            // PP
            if(find == true){

                printf("Número de página: %d\n", TLB[indTrue].pag);
                printf("Desplazamiento: %d\n", TLB[indTrue].des);
                clock_t end = clock();
                tEjec += (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Tiempo de ejecución: %f segundos\n", tEjec);
                printf("TLB HIT\n\n");

            } else{
                
                //Obtenemos el número de página y el desplazamiento
                int nDes = dirIngresada % 4096; int nPag = (int) (dirIngresada / 4096);
                printf("Número de página: %d\n", nPag);
                printf("Desplazamiento: %d\n", nDes);
                clock_t end = clock();
                tEjec += (double)(end - begin) / CLOCKS_PER_SEC;
                printf("Tiempo de ejecución: %f segundos\n", tEjec);
                printf("TLB MISS\n\n");

                //Creamos el struct
                obj.dir = dirIngresada;
                obj.pag = nPag;
                obj.des = nDes;

                //Agregamos el struct al array
                TLB[ind] = obj;
                if(ind == 9){
                    ind = 0;
                } else {
                    ind++;
                }

            }

        } else {

            break;

        }

    }
}

