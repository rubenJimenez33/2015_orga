#include <stdio.h>
#include <stdlib.h>
#define ayuda 'h'
#define version 'V'
#define caracteres 'c'
#define lineas 'n'
#define cantLineasPorDefecto 10
#define maxcantArchivos 50
#define tamanioMaximoLinea 2000
typedef int bool;
#define true 1
#define false 0
/*
struct nodo_string{
   char* string;
   struct nodo_string *siguiente;
};

struct nodo_char{
   char caracter;
   struct nodo_char *siguiente;
};

struct cola_char{
   struct nodo_char *primero;
   struct nodo_char *ultimo;
};
*/


/*****   $tp0 -c 10 -n 2 <prueba.txt   ***/


void evaluarArgumentos();
void validacionEntero(int numero);
void imprimirAyuda();
void imprimirVersion();
void tail(int i,char* archivos[],int cantArchivos,bool caso);
void imprimirLineas(char* bufferString[],int cantLineasLeidas, int cantLineas, int ultimo);
void imprimirCaracteres(char bufferCaracter[],int cantCaracteresLeidos,int cantCaracteres, int ultimo);
char* getLinea(FILE *fp);

int main (int argc, char *argv[])
{
    evaluarArgumentos(argc,argv);
    printf("\n¡Fin del programa!\n");
    return 0;
}


void evaluarArgumentos(int argc, char *argv[])
{
    int i = 0;
    char *nombresArchivos[maxcantArchivos];
    int cantArchivos = 0;
    bool LineasPorDefecto = true;
    int evaluadorCaracterLinea = 0;


    for(i=1;i<argc;i++)                      /*buscamos los archivos*/
    {
            if (*argv[i] == '-')             //descartamos las opciones
            {
                    i++;                    //avanzamos al siguiente arguemento
                    switch ( *(argv[i] +1) )
                    {
                            case caracteres:
                            i++;            //si es caracter descartamos su parametro k
                            evaluadorCaracterLinea++;
                            break;

                            case lineas:    //si es linea descartamos su parametro k
                            evaluadorCaracterLinea++;
                            i++;
                            break;
                    }
            }
            else
            {
                    nombresArchivos[cantArchivos++]  = argv[i];
            }
    }

    if(evaluadorCaracterLinea > 1)
    {
        char* error_doble_funcionalidad = "\n error en los parametros, usar -n o -c pero no ambos \n";
        fputs(error_doble_funcionalidad,stderr);
        exit(1);
    }


        for (i = 1;i<argc;i++)   //no contamos el argumento cero dado que es el programa, ni el ultimo porque es el archivo
        {
                if (*argv[i] == '-')
                    switch ( *(argv[i] +1) )
                    {
                            case ayuda:
                            imprimirAyuda();
                            break;

                            case version:
                            imprimirVersion();
                            break;

                            case caracteres:
                            validacionEntero(atoi(argv[i+1]));
                            tail(atoi(argv[i+1]),nombresArchivos,cantArchivos,false);
                            LineasPorDefecto = false;
                            break;

                            case lineas:
                            validacionEntero(atoi(argv[i+1]));
                            tail(atoi(argv[i+1]),nombresArchivos,cantArchivos,true);
                            LineasPorDefecto = false;
                            break;

                            default:
                            imprimirAyuda();    //imprimir ayuda en caso de parametros incorrectos
                            exit(1);
                            break;
                    }
        }

        if(LineasPorDefecto == true)
            tail(cantLineasPorDefecto,nombresArchivos,cantArchivos,true);

}


void tail(int cantLineaschar,char* archivos[],int cantArchivos,bool caso)
{
    FILE *fp;
    int i = 0;
    char* error_parametro = "\n error la cantidad de lineas/caracteres es mayor a la que contiene el archivo \n";
    do
    {
            if (cantArchivos < 1)
            {
                    fp = stdin;
            }

            else
            {
                    if ((fp = fopen(archivos[i],"r")) == NULL)
                            fputs("error el archivo no existe\n",stderr);
            }

            if (caso == true) //lineas
            {
                    char* bufferString[cantLineaschar];
                    char* string;
                    int cantLineasLeidas = -1;
                    int ultimo = 0;
                    while( (string = getLinea(fp)) != NULL )
                    {
                            ++cantLineasLeidas;
                            ultimo = cantLineasLeidas % cantLineaschar;
                            bufferString[ultimo] = string;
                    }

                    if(cantLineasLeidas < cantLineaschar)
                    {
                            fputs(error_parametro,stderr);
                            exit(1);
                    }
                    else
                    {
                             imprimirLineas(bufferString,cantLineasLeidas,cantLineaschar,ultimo);
                    }
            }

            else
            {
                    char bufferCaracter[cantLineaschar];
                    char caracter;
                    int cantCaracteresLeidos = 0;
                    int ultimo = 0;

                    while( (caracter =fgetc(fp)) != EOF )
                    {
                            cantCaracteresLeidos++;
                            ultimo = cantCaracteresLeidos % cantLineaschar;
                            bufferCaracter[ultimo] = caracter;

                    }
 /*                   printf("\n++++++++++++++++++++++++++++++");
                    printf("%c",bufferCaracter[ultimo]);
                    printf("++++++++++++++++++++++++++++++\n");
*/
                    if(cantCaracteresLeidos < cantLineaschar)
                    {
                            fputs(error_parametro,stderr);
                            exit(1);
                    }
                    else
                    {
                             imprimirCaracteres(bufferCaracter,cantCaracteresLeidos, cantLineaschar,ultimo);
                    }
            }

            i++;

    }
    while(i<cantArchivos);

}

void imprimirAyuda()
{
    printf("Ayuda =/ \n");
}

void imprimirVersion()
{
    printf("Version \n");
}


void validacionEntero(int numero)
{
    if(numero <= 0)
    {
            char* salida = "error en el parametro de lineas o caracteres ";
            fputs(salida,stderr);
            exit(1);
    }

}

void imprimirLineas(char* bufferString[],int cantLineasLeidas, int cantLineas, int ultimo)
{
    printf("\n ****las ultimas lineas escritas**** \n ");

    if(cantLineasLeidas > cantLineas)       //se solaparon valores al llenarse el buffer
    {
            int inicio = 0;
            for(inicio = (ultimo+1)%cantLineas; inicio < cantLineas; inicio++) //sin contar el ultimo caracter de salida
            {
                    printf(" ---->");
                    fputs(bufferString[inicio],stdout);
                    printf("\n");
            }

            if( (ultimo+1) != cantLineas )
            {
                    for(inicio = 0; inicio <= ultimo; inicio++)
                    {
                            printf(" ---->");
                            fputs(bufferString[inicio],stdout);
                            printf("\n");
                    }
            }
    }
/*    else
    {
            int inicio = 0;
            for(inicio = 0; inicio < cantLineasLeidas; inicio++)
            {
                    printf("\n");
                    fputs(bufferString[inicio],stdout);
            }
    }
 */
}

void imprimirCaracteres(char bufferCaracter[],int cantCaracteresLeidos,int cantCaracteres, int ultimo)
{
    printf("\n ****los ultimos caracteres escritos**** \n ");
    printf(" ---->");

    if(cantCaracteresLeidos > cantCaracteres)       //se solaparon valores al llenarse el buffer
    {
            int inicio = 0;
            for(inicio = (ultimo+1)%cantCaracteres; inicio < cantCaracteres; inicio++) //sin contar el ultimo caracter de salida
            {
                    fputc(bufferCaracter[inicio],stdout);
            }

            if( (ultimo+1) != cantCaracteres)
            {
                    for(inicio = 0; inicio <= ultimo; inicio++)
                    {
                            fputc(bufferCaracter[inicio],stdout);
                    }
            }
    }
/*    else
    {
            int inicio = 0;
            for(inicio = 0; inicio < cantCaracteres; inicio++)
            {
                    fputc(bufferCaracter[inicio],stdout);
            }
    }
*/
    fputs("<----",stdout);
   // printf("<----");
}

char* getLinea(FILE *fp)
{
    char finDeLinea = '\n';
    char* retorno = malloc(tamanioMaximoLinea*sizeof(char));
    int indice = 0;
    char caracter;

    caracter = getc(fp);

    while( caracter != finDeLinea &&  caracter != EOF )
    {
            *(retorno + indice) = caracter;
            indice++;
            caracter = getc(fp);
    }

    if(caracter == EOF && indice == 0)
    {
            retorno = NULL;
    }

    return retorno;
}
