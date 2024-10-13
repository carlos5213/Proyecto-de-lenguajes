#include<stdio.h>
#include<stdlib.h>

typedef struct nodo
{
  char nombre[30];
  int edad;
  char sexo;
  float altura;
  double peso;
  struct nodo *sig;
}GEN;


int asignaMem(GEN **ptr, int n){
 int res = 0, cont;
 *ptr = (GEN *)malloc(sizeof(GEN));
if(*ptr)
{
  res = 1;
  for(cont = 0; cont < n && res; cont++)
    {
      printf("Escriba datos del paciente:\n");
      printf("Nombre:\n");
      printf("Edad:\n");
      printf("Sexo:\n");
      printf("Altura:\n");
      printf("Peso:\n");
    }
}
}

int creaNodo(GEN *nuevo, char nombre[], int edad, char sexo, float altura, double peso)
{
  
}


int main()
{
  int tambloque = sizeof(struct nodo);
  void *ptrGen;
}