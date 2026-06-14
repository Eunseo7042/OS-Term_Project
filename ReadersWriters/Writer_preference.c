#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2

int read_count = 0;
int write_count = 0;
int shared_data = 0;

sem_t resource;
sem_t readTry;
sem_t rmutex;
sem_t wmutex;

void *reader(void *arg)
{
    int id = *((int *)arg);

    for(int i = 0; i < 3; i++)
    {
        sem_wait(&readTry);

        sem_wait(&rmutex);
        read_count++;

        if(read_count == 1)
            sem_wait(&resource);

        sem_post(&rmutex);

        sem_post(&readTry);

        printf("Reader %d reads data = %d\n", id, shared_data);

        sleep(1);

        sem_wait(&rmutex);
        read_count--;

        if(read_count == 0)
            sem_post(&resource);

        sem_post(&rmutex);

        sleep(1);
    }

    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    for(int i = 0; i < 3; i++)
    {
        sem_wait(&wmutex);
        write_count++;

        if(write_count == 1)
            sem_wait(&readTry);

        sem_post(&wmutex);

        sem_wait(&resource);

        shared_data++;
        printf("Writer %d writes data = %d\n", id, shared_data);

        sleep(1);

        sem_post(&resource);

        sem_wait(&wmutex);
        write_count--;

        if(write_count == 0)
            sem_post(&readTry);

        sem_post(&wmutex);

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t r[READERS], w[WRITERS];

    int rid[READERS];
    int wid[WRITERS];

    sem_init(&resource, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);

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

    sem_destroy(&resource);
    sem_destroy(&readTry);
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);

    return 0;
}

