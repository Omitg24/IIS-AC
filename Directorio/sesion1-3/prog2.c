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

void swap(int* x, int* y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sort(int array[], int start, int end)
{
  int l, r, p;
  if (start < end) {
    l = start +1;
    r = end;
    p = array[start];
    while (l < r) {
      if (array[l] <= p)
        l++;
      else if (array[r] >= p)
        r--;
      else
        swap(&array[l], &array[r]);
    }
    if (array[l] < p)
    {
      swap(&array[l], &array[start]);
      l--;
    }
    else
    {
      l--;
      swap(&array[l], &array[start]);
    }
    sort(array, start, l);
    sort(array, r, end);
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
  sort(vector1, 0, TAM - 1);

  return EXIT_SUCCESS;
}

