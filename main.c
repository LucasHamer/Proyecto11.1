#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int ndecanal;
    char programa[35];
    float rating;
}Sprograma;

typedef struct
{
    int ndecanal2;
    float promedio;
}Sprom;

void mostrar2();
void mostrar();
void generar();

int main()
{
    //generar();
    mostrar2();
    int antcanal,programas,primero=1,canalmax;
    float sumarating,max;
    Sprograma progra;
    Sprom prom;
    FILE*fp,*fm;
    fp=fopen("rating.dat","rb");
    fm=fopen("promedio.dat","wb");
    if(fp==NULL||fm==NULL)
    {
        printf("Error");
        system("pause");
        exit(3);
    }
    fread(&progra,sizeof(Sprograma),1,fp);
    while(!feof(fp))
    {
        antcanal=progra.ndecanal;
        sumarating=0;
        programas=0;
        while(antcanal==progra.ndecanal&&!feof(fp))
        {
            sumarating+=progra.rating;
            programas++;
            fread(&progra,sizeof(Sprograma),1,fp);
        }
        if(sumarating<15)
            printf("El canal %d obtuvo menos de 15 de rating. Obtuvo: %.2f\n",antcanal,sumarating);
        if(primero||sumarating>max)
        {
            max=sumarating;
            canalmax=antcanal;
            primero=0;
        }
        prom.ndecanal2=antcanal;
        prom.promedio=sumarating/programas;
        fwrite(&prom,sizeof(Sprom),1,fm);
    }
    fclose(fp);
    fclose(fm);

    if(!primero)
    printf("El canal mas visto fue %d con %.2f puntos de rating",canalmax,max);

    mostrar();

    return 0;
}
void generar()
{
    Sprograma progra;
    FILE*fp;
    fp=fopen("rating.dat","wb");
    while(fp==NULL)
    {
        printf("Error al abrir");
        system("pause");
        exit(1);
    }
    printf("Ingrese n de canal: ");
    scanf("%d",&progra.ndecanal);
    while(progra.ndecanal!=0)
    {
    printf("Ingrese programa: ");
    fflush(stdin);
    gets(progra.programa);
    printf("Ingrese rating: ");
    scanf("%f",&progra.rating);
    printf("Ingrese n de canal: ");
    scanf("%d",&progra.ndecanal);
    fwrite(&progra,sizeof(Sprograma),1,fp);
    }
}
void mostrar2()
{
    Sprograma progra;
    FILE*fp;
    fp=fopen("rating.dat","rb");
    if(fp==NULL)
    {
        printf("Error al abrir");
        system("pause");
        exit(4);
    }
    fread(&progra,sizeof(Sprograma),1,fp);
    while(!feof(fp))
    {
        printf("\nCanal %d        Programa %s       Rating %.2f\n",progra.ndecanal,progra.programa,progra.rating);
        fread(&progra,sizeof(Sprograma),1,fp);
    }
    fclose(fp);
}
void mostrar()
{
    Sprom prom;
    FILE*fm;
    fm=fopen("promedio.dat","rb");
    if(fm==NULL)
    {
        printf("Error al abrir");
        system("pause");
        exit(2);
    }
    fread(&prom,sizeof(Sprom),1,fm);
    while(!feof(fm))
    {
        printf("\nCanal %d        Promedio %.2f\n",prom.ndecanal2,prom.promedio);
        fread(&prom,sizeof(Sprom),1,fm);
    }
    fclose(fm);
}
