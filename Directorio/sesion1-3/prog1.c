#include <stdlib.h>

#define TAM 100000

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

void rellenarConAleatorios(int array[], int n)
{
  int i;

  // Inicialización del generador aleatorio
  static int semilla = 0;
  srand(semilla++);

  // Generación de números entre 1 y 1000 
  for (i = 0; i < n ; i++) 
    array[i] = rand() % 1000 + 1;
}

void ordenarVector(int* vector, int tamVector)
{
  int i, j, iMin, temp;

  // Ordenación por el método de selection sort
  for (i = 0; i < tamVector; i++) 
  {
    iMin = i;
    for (j = i+1; j < tamVector; j++)
    {
      if (vector[j] < vector[iMin])
      {
        iMin = j;
        temp = vector[i];
        vector[i] = vector[iMin];
        vector[j] = temp;
      }
    }
  }
}

BOOLEAN estaEnVector(int num, int vector[], int tamVector)
{
  int i;

  for (i = 0; i < tamVector; i++)
  { 
    if (vector[i] == num)
    { 
      return TRUE;
    }
  }
  return FALSE;
}

BOOLEAN esPrimo(int n)
{
  int i;

  for (i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      return FALSE;
    }
  }
  return TRUE;
}

int contarPrimosComunes(int vector1[], int tamVector1, int vector2[], int tamVector2)
{
  int numPrimosComunes = 0;
  int i;

  for (i = 0; i < tamVector1; i++)
  { 
    if (estaEnVector(vector1[i], vector2, tamVector2) && esPrimo(vector1[i]))
    {
      numPrimosComunes++;
    }
  }

  return numPrimosComunes;
}

int main()
{
  int vector1[TAM];
  int vector2[TAM];

  rellenarConAleatorios(vector1, TAM);
  rellenarConAleatorios(vector2, TAM);

  contarPrimosComunes(vector1, TAM, vector2, TAM);
  ordenarVector(vector1, TAM);

  return EXIT_SUCCESS;
}

