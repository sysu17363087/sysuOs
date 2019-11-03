#include "shmfifo.h"
#include <math.h>
#include <stdlib.h>
#define N 20 
#define consumerNum  3
double randomExponential(double pV)
{
    double lambda = 0.5;
    pV = (1.0/lambda)*log(pV-1);
    return pV;
}
double ct;
typedef struct Msg
{
  char number[N];
  int place;
}msg_t;

void * consumer(void *b){
  shmfifo_t *fifo=shmfifo_init(12,3,sizeof(msg_t));
  msg_t *msg=(msg_t*)malloc(sizeof(msg_t));
  int i=0;
  for(i=0;i<N/3;i++)
  {
    shmfifo_get(fifo,msg);
    printf("process id: %d  thread id: %lu\n", getpid(),pthread_self());
    sleep(randomExponential(ct));
  }
  shmfifo_destroy(fifo);
}

int main(int agrc,char argv[])
{
	ct = (double)argv[1];

    pthread_t threadPool[consumerNum];
    int i;
    for(i = 0; i < consumerNum; i++){
        pthread_t temp;
        if(pthread_create(&temp, NULL, consumer, NULL) == -1){
            printf("ERROR, fail to create consumer%d\n", i);
        }
        threadPool[i] = temp;
    }//创建消费者进程放入线程池*


    void * result;
    for(i = 0; i < consumerNum; i++){
        if(pthread_join(threadPool[i], &result) == -1){
            printf("fail to recollect\n");
        }
    }//运行线程池
  return 0;

}


