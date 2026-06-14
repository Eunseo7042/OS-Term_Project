#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER 30
#define ITER 100

int buffer_count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg)
{
    for(int i=0;i<ITER;i++)
    {
        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        buffer_count++;
        printf("Producer -> Buffer = %d\n", buffer_count);

        pthread_mutex_unlock(&mutex);

        sem_post(&full);

    }

    return NULL;
}

void* consumer(void* arg)
{
    for(int i=0;i<ITER;i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        buffer_count--;
        printf("Consumer -> Buffer = %d\n", buffer_count);

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);

    }

    return NULL;
}

int main()
{
    pthread_t p,c;

    sem_init(&empty,0,MAX_BUFFER);
    sem_init(&full,0,0);

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);

    return 0;
}
