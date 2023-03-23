// compilar com gcc -pthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void *t_function(void *arg){
	printf("Nova thread em execução!\n");
	sleep(3);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[NUM_THREADS];
  int i;
  
  for (i = 0 ; i < NUM_THREADS; i++){  
	printf("Thread %d sendo criada\n",i);
	pthread_create(&t[i],NULL,t_function,NULL); 
  }
  printf("Aguardando termino das threads\n");
  
  for(i=0; i < NUM_THREADS; i++)
	pthread_join(t[i],NULL);
  return 0;
}

