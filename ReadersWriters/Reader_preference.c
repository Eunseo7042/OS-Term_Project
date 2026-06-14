#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2

int read_count = 0;
int shared_data = 0;

sem_t mutex;
sem_t wrt;

void *reader(void *arg)
{
    int id = *((int *)arg);

    for(int i = 0; i < 3; i++)
    {
        sem_wait(&mutex);
        read_count++;

        if(read_count == 1) //reader가 계속 들어옴
            sem_wait(&wrt); //reader가 들어오는 동안 wirter는 기다림

        sem_post(&mutex);

        printf("Reader %d reads data = %d\n", id, shared_data);

        sleep(1);

        sem_wait(&mutex);
        read_count--;

        if(read_count == 0)
            sem_post(&wrt);

        sem_post(&mutex);

        sleep(1);
    }

    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    for(int i = 0; i < 3; i++)
    {
        sem_wait(&wrt);

        shared_data++;
        printf("Writer %d writes data = %d\n", id, shared_data);

        sem_post(&wrt);

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t r[READERS], w[WRITERS];

    int rid[READERS];
    int wid[WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for(int i = 0; i < READERS; i++)
    {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }

    for(int i = 0; i < WRITERS; i++)
    {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }

    for(int i = 0; i < READERS; i++)
        pthread_join(r[i], NULL);

    for(int i = 0; i < WRITERS; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
