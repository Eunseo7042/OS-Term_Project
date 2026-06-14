#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void *philosopher(void *arg)
{
    int id = *((int *)arg);

    int left = id;
    int right = (id + 1) % N;

    for(int i=0;i<3;i++)
    {
        printf("Philosopher %d thinking\n", id);
        sleep(1);

        int first = left < right ? left : right;
        int second = left < right ? right : left;

        pthread_mutex_lock(&forks[first]);
        pthread_mutex_lock(&forks[second]);

        printf("Philosopher %d eating\n", id);
        sleep(1);

        pthread_mutex_unlock(&forks[second]);
        pthread_mutex_unlock(&forks[first]);
    }

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

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

