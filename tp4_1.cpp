#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void vaciar_buffer();
struct Tarea{
    int TareaID;       //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
};

struct Nodo{
    Tarea T;
    Nodo* Siguiente;
};

void mostrarTarea(Tarea);

void cargarRealizadas(Nodo **pLista,Nodo **pRealizadas){
    Nodo * ant=*pLista;
    Nodo* aux=*pLista;
    Nodo * ant2;
    Nodo* aux2;
    while(aux!=NULL){
        mostrarTarea((*aux).T);
        bool flag = false;
        ant2=aux;
        aux2=(*aux).Siguiente;
        do{
            flag = false;
            printf("Ya completó esta tarea? (S/n)\n");
            char resp;

            vaciar_buffer(); //El fflush No funciona (ni está indicado) para borrar el búfer de entrada, así que defino esta funcion
            scanf("%c", &resp);
            if (resp == 's' || resp == 'S'){
                if (aux==*pLista)//primer elemento
                    (*pLista)=(*aux).Siguiente;
                else
                    (*ant).Siguiente=(*aux).Siguiente;
                (*aux).Siguiente=*pRealizadas;
                *pRealizadas = aux;
                ant2=ant;
            }
            else if (!(resp == 'n' || resp == 'N')){
                flag = true;
                printf("Respuesta inválida, intente de nuevo\n");
            }
        } while (flag);
        ant=ant2;
        aux=aux2;
    }
}

void cargarTareas(Nodo **pLista, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        char s[100]; //String auxiliar
        Nodo* n = (Nodo *)malloc(sizeof(Nodo));
        (*n).Siguiente=*pLista;
        (*pLista)=n;
        (*n).T.TareaID = i;
        printf("Ingrese la descripción de la tarea: ");

        scanf("%s", s);

        (*n).T.Descripcion = (char *)malloc(sizeof(s) * strlen(s));
        strcpy(((*n).T.Descripcion), s);

        int duracion=rand()%101+10;
        (*n).T.Duracion=duracion;
    }
    
}

Tarea *buscarTareaPorID(int idTarea,Nodo * pTareas1,Nodo * pTareas2){
    Nodo * nAux=(pTareas1);
    bool flag=true;
    for (int i = 0; i < 2; i++)
    {
        while (nAux!=NULL){
            if ((*nAux).T.TareaID==idTarea)
                return &(*nAux).T;
            else
                nAux=(*nAux).Siguiente;
        }
        nAux=(pTareas2);
    }
    printf("\n\t\tNo se encontró la tarea\n");
    return NULL;
}

Tarea *buscarTareaPorPalabra(char clave[], Nodo *pTareas1, Nodo *pTareas2){
    Nodo *nAux=pTareas1;
    for (int i = 0; i < 2; i++)
    {
        while (nAux!=NULL){
            if (strstr((*nAux).T.Descripcion, clave) != NULL)
                return &(*nAux).T;
            else
                nAux=(*nAux).Siguiente;
        }
        nAux=pTareas2;
    }
    printf("\n\t\tNo se encontró la tarea\n");
    return NULL;
}

void mostrarTarea(Tarea t){
    printf("\nID de la Tarea: %d\n"\
            "Descripción: %s\n"\
            "Duración: %d\n",
            t.TareaID, t.Descripcion,
            t.Duracion);
}

void mostrarTareas(Nodo *pLista){
    Nodo* aux=pLista;
    while (aux!=NULL){
        mostrarTarea((*aux).T);
        aux=(*aux).Siguiente;
    }
}

int main(int argc, char const *argv[]){
    printf("Cuántas tareas va a cargar?: ");
    int cantTareas;
    scanf("%d", &cantTareas);
    Nodo * pTareas=NULL;
    cargarTareas(&pTareas,cantTareas);
    Nodo *pTareasRealizadas=NULL;
    cargarRealizadas(&pTareas,&pTareasRealizadas);

    printf("\n\n\tTareas Pendientes\n");
    mostrarTareas(pTareas);

    printf("\n\tTareas Realizadas\n");
    mostrarTareas(pTareasRealizadas);

    printf("\n\tBúsqueda por ID\n");
    Tarea *t = buscarTareaPorID(3,pTareasRealizadas,pTareas);
    if (t!=NULL)
    {
        mostrarTarea(*t);
    }
    printf("\n\tBúsqueda por palabra\n");
    t = buscarTareaPorPalabra("a", pTareasRealizadas, pTareas);
    if (t!=NULL)
    {
        mostrarTarea(*t);
    }
    
    
    
    free(pTareas);
    free(pTareasRealizadas);
    getchar();
    printf("\n\n");
    return 0;
    }

    void vaciar_buffer()
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }