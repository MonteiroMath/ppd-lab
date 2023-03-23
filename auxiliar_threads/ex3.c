// compilar com gcc -pthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 2

typedef struct retangulo_t{
	double base;
	double alt;
} retangulo;

void *t_function(void *arg){
   retangulo *r;
   r = (retangulo *)arg;
	printf("b=%.2f, a=%.2f, area=%.2f\n",r->base,r->alt,r->base*r->alt);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[NUM_THREADS];
  //long t_num;  /* Use long if 64-bit system */
  long i;
  retangulo *r1,*r2;

  r1 = malloc(sizeof(retangulo));
  r1->alt = 4;
  r1->base = 3;
  
  r2 = malloc(sizeof(retangulo));
  r2->alt = 4.2;
  r2->base = 1.3;
    
  printf("Criando a thread 1\n");
  pthread_create(&t[0],NULL,t_function,(void *)r1);
  
  printf("Criando a thread 2\n");
  pthread_create(&t[1],NULL,t_function,(void *)r2);
  
    printf("Aguardando termino das threads\n");
  for(i=0; i < NUM_THREADS; i++)
	pthread_join(t[i],NULL);
  printf("Threads terminaram\n");
  return 0;	
}
