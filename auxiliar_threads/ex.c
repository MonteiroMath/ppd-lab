// compilar com gcc -pthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 2

typedef struct retangulo_t{
	double base;
	double alt;
} retangulo;

void *t_function(void *arg){
	retangulo *r;
	r = (retangulo *)arg;
	printf("b=%.2f, a=%.2f, area=%.2f\n",r->base,r->alt,(r->base*r->alt));
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[NUM_THREADS];
  retangulo *r1, *r2;
  long i;
  
  r1 = malloc(sizeof(retangulo));
  r1->base = 3;
  r1->alt = 4;
  
  r2 = malloc(sizeof(retangulo));
  r2->base = 3.4;
  r2->alt = 7;
  
  printf("Thread 1 sendo criada\n");
  pthread_create(&t[0],NULL,t_function,(void *)r1); 
 
  printf("Thread 2 sendo criada\n");
  pthread_create(&t[1],NULL,t_function,(void *)r2); 
 
  printf("Aguardando termino das threads\n");
  
  for(i=0; i < NUM_THREADS; i++)
	pthread_join(t[i],NULL);
  return 0;
}
