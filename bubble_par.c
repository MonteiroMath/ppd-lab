// Compilar:
// gcc -o bubble_par bubble_par.c -pthread
// ./bubble_par 2 10

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define IMPRIME
#define NUM_THREADS 2 // lembrar de ajustar número de threads de acordo com o número de parâmetros

int bubble(int *array, unsigned int size)
{

  int i, j;
  int temp;

  for (i = 0; i < size - 1; i++)
  {

    for (j = 0; j < size - i - 1; j++)
    {

      if (array[j] > array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// definição de struct para passagem de argumentos para a função da thread
typedef struct
{
  int **arrays;
  int n_arrays;
  int tam;
  int thread_num;
} t_args;

// definição da função da thread
void *t_function(void *arg)
{

  int i;
  t_args *targ;
  targ = (t_args *)arg;

  // printf("args: \n  n: %d; tam: %d, t_num: %d\n", targ->n_arrays, targ->tam, targ->thread_num);
  // printf("\nconditions:\n start: %d; end:%d\n", targ->thread_num * (targ->n_arrays / NUM_THREADS), (targ->thread_num + 1) * (targ->n_arrays / NUM_THREADS));

  for (i = targ->thread_num * (targ->n_arrays / NUM_THREADS); i < (targ->thread_num + 1) * (targ->n_arrays / NUM_THREADS); i++)
  {
    bubble(targ->arrays[i], targ->tam);
  }

  pthread_exit(NULL);
}

void imprime(int **array, int num_arrays, int size)
{
  int i, j;
  for (i = 0; i < num_arrays; i++)
  {
    for (j = 0; j < size; j++)
    {
      printf("%d ", array[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv)
{
  // inicialização de array de threads e argumentos
  pthread_t t[NUM_THREADS];
  t_args *targs[NUM_THREADS];
  int **elementos, n, tam, i, j;
  struct timeval t1, t2;
  double t_total;

  if (argc != 3)
  {
    printf("Digite %s Num_arrays Num_elementos\n", argv[0]);
    exit(0);
  }
  n = atoi(argv[1]);
  tam = atoi(argv[2]);

  // srand(time(NULL));

  /*Aloca memória para os vetores*/
  elementos = (int **)malloc(n * sizeof(int *));
  for (i = 0; i < n; i++)
    elementos[i] = (int *)malloc(tam * sizeof(int));

  /*Popula os arrays com elementos aleatorios entre 0 e 1000*/
  for (i = 0; i < n; i++)
    for (j = 0; j < tam; j++)
      elementos[i][j] = rand() % 1000;

#ifdef IMPRIME
  printf("Antes da ordenacao!\n");
  imprime(elementos, n, tam);
  printf("\n");
#endif

  gettimeofday(&t1, NULL);

  for (i = 0; i < NUM_THREADS; i++)
  {
    // aloca memória e configura argumentos
    targs[i] = (t_args *)malloc(sizeof(t_args));
    targs[i]->arrays = elementos;
    targs[i]->n_arrays = n;
    targs[i]->tam = tam;
    targs[i]->thread_num = i;

    printf("Thread %d sendo criada\n", i);
    pthread_create(&t[i], NULL, t_function, (void *)targs[i]);
  }
  printf("Aguardando termino das threads\n");

  for (i = 0; i < NUM_THREADS; i++)
    pthread_join(t[i], NULL);

  // libera memória alocada para argumentos
  for (i = 0; i < NUM_THREADS; i++)
    free(targs[i]);

  gettimeofday(&t2, NULL);

  t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);

#ifdef IMPRIME
  printf("apos a ordenacao!\n");
  imprime(elementos, n, tam);
  printf("\n");
#endif

  /*Libera memoria alocada*/
  for (i = 0; i < n; i++)
  {
    free(elementos[i]);
  }
  free(elementos);

  printf("tempo total = %f\n", t_total);

  return 0;
}
