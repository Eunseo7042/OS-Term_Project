#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];
pthread_mutex_t table_lock;

void *philosopher(void *arg)
{
    int id = *((int *)arg);

    for(int i=0;i<3;i++)
    {
        printf("Philosopher %d is waiting\n", id);
        sleep(1);

        pthread_mutex_lock(&table_lock);

        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id+1)%N]);

        pthread_mutex_unlock(&table_lock);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id+1)%N]);
    }

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    pthread_mutex_init(&table_lock,NULL);

    for(int i=0;i<N;i++)
        pthread_mutex_init(&forks[i],NULL);

    for(int i=0;i<N;i++)
    {
        id[i]=i;
        pthread_create(&p[i],NULL,philosopher,&id[i]);
    }

    for(int i=0;i<N;i++)
        pthread_join(p[i],NULL);

    return 0;
}
