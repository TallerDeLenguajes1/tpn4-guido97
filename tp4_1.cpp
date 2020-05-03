#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void vaciar_buffer();
struct Tarea
{
    int TareaID;       //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
};
void mostrarTarea(Tarea);

void cargarRealizadas(Tarea **pVector, Tarea **pRealizadas, int cant)
{

    for (int i = 0; i < cant; i++)
    {
        mostrarTarea(*pVector[i]);
        bool flag = false;
        do
        {
            flag = false;
            printf("Ya completó esta tarea? (S/n)\n");
            char resp;

            vaciar_buffer(); //El fflush No funciona (ni está indicado) para borrar el búfer de entrada, así que defino esta funcion
            scanf("%c", &resp);
            if (resp == 's' || resp == 'S')
            {
                pRealizadas[i] = pVector[i];
                pVector[i] = NULL;
                //Borrar de pendientes y pasar a realizados
            }
            else if (!(resp == 'n' || resp == 'N'))
            {
                flag = true;
                printf("Respuesta inválida, intente de nuevo\n");
            }
        } while (flag);
    }
}

void cargarTareas(Tarea **pVector, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        char s[100]; //String auxiliar
        pVector[i] = (Tarea *)malloc(sizeof(Tarea *));
        (*pVector[i]).TareaID = i;
        printf("Ingrese la descripción de la tarea: ");

        scanf("%s", s);

        (*pVector[i]).Descripcion = (char *)malloc(sizeof(s) * strlen(s));
        strcpy(((*pVector[i]).Descripcion), s);

        int duracion=rand()%101+10;
        (*pVector[i]).Duracion=duracion;
    }
    
}
Tarea buscarTareaPorID(int idTarea,Tarea ** pTareas1,Tarea ** pTareas2,int cantTareas){
    Tarea *tAux;
    for (int i = 0; i < cantTareas; i++)
    {
        if ((tAux=(pTareas1[i]))==NULL)
            tAux=pTareas2[i];
        
        if ((*tAux).TareaID==idTarea)
            return *tAux; 
    }
    return *tAux;
}


Tarea buscarTareaPorPalabra(char clave[], Tarea **pTareas1, Tarea **pTareas2, int cantTareas){
    Tarea *tAux;
    for (int i = 0; i < cantTareas; i++)
    {
        if ((tAux = (pTareas1[i])) == NULL)
            tAux = pTareas2[i];

        if (strstr((*tAux).Descripcion, clave) != NULL)
        {
            return *tAux;
        }

    }
    return *tAux;
}

    void mostrarTarea(Tarea t){
printf("\nID de la Tarea: %d\n"\
                "Descripción: %s\n"\
               "Duración: %d\n",
               t.TareaID, t.Descripcion,
               t.Duracion);
    }


    void mostrarTareas(Tarea **pVector, int cant)
    {
        for (int i = 0; i < cant; i++)
            if (pVector[i] != NULL)
            {
                mostrarTarea(*pVector[i]);
            }
    }

int main(int argc, char const *argv[])
{
    printf("Cuántas tareas va a cargar?: ");
    int cantTareas;
    scanf("%d", &cantTareas);
    Tarea **pTareas;
    pTareas = (Tarea **)malloc(sizeof(Tarea*)*cantTareas);
    cargarTareas(pTareas,cantTareas);
    Tarea **pTareasRealizadas = (Tarea **)malloc(sizeof(Tarea*)*cantTareas);
    cargarRealizadas(pTareas,pTareasRealizadas,cantTareas);

    printf("\n\n\tTareas Pendientes\n");
    mostrarTareas(pTareas,cantTareas);

    printf("\n\tTareas Realizadas\n");
    mostrarTareas(pTareasRealizadas,cantTareas);

    printf("Búsqueda por ID\n");
    Tarea t = buscarTareaPorID(3,pTareasRealizadas,pTareas,cantTareas);
    mostrarTarea(t);

    printf("Búsqueda por palabra\n");
    t = buscarTareaPorPalabra("a", pTareasRealizadas, pTareas, cantTareas);
        mostrarTarea(t);

        free(pTareas);
        free(pTareasRealizadas);
        getchar();
        return 0;
    }

    void vaciar_buffer()
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }