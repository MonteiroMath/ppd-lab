// compilar com gcc -pthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void *t_function(void *arg){
    long *rank;
    rank = (long *)arg;
	printf("Thread #%ld em execução!\n",*rank);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t t[NUM_THREADS];
  //long t_num;  /* Use long if 64-bit system */
  long i;
  long *ids[NUM_THREADS];

   //t = malloc(total_threads*sizeof(pthread_t));

  for (i = 0 ; i < NUM_THREADS; i++){
	 ids[i] = malloc(sizeof(long)*1);   
     *ids[i] = i;
     printf("Ciando a thread %ld , %ld\n",i,*ids[i]);
     pthread_create(&t[i],NULL,t_function,(void *)ids[i]);
  }
  printf("Aguardando termino das threads\n");
  for(i=0; i < NUM_THREADS; i++)
	pthread_join(t[i],NULL);
  printf("Threads terminaram\n");
  return 0;	// pode usar tambem macros EXIT_SUCCESS
}
