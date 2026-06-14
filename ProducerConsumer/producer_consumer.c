#include <pthread.h>
#include <stdio.h>

#define ITER 1000

void *thread_increment(void *arg);
void *thread_decrement(void *arg);

int x = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 뮤텍스 초기화
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_increment, NULL);
    pthread_create(&tid2, NULL, thread_decrement, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (x != 0)
        printf("BOOM! counter=%d\n", x);
    else
        printf("OK counter=%d\n", x);

    pthread_mutex_destroy(&mutex);
    return 0;
}

void *thread_increment(void *arg) {
    int i, val;
    for (i = 0; i < ITER; i++) {
        pthread_mutex_lock(&mutex);

        //0~30
        while(x >= 30){
            pthread_cond_wait(&cond, &mutex);
        }
        val = x;
        printf("%u: %d\n", (unsigned int) pthread_self(), val);
        x = val + 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

void *thread_decrement(void *arg) {
    int i, val;
    for (i = 0; i < ITER; i++) {
        pthread_mutex_lock(&mutex);
        while(x <= 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        val = x;
        printf("%u: %d\n", (unsigned int) pthread_self(), val);
        x = val - 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


/*
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
*/
