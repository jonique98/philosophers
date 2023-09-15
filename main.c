#include <stdio.h>
#include <pthread.h>
 #include <sys/time.h>
 #include <stdlib.h>

pthread_mutex_t mutex;

void *hi(void *a) {
    struct timeval time;
    a = 0;

while (1)
{
    pthread_mutex_lock(&mutex);

    gettimeofday(&time, NULL);
    pthread_mutex_unlock(&mutex);
}


    return a;
}

int main() {

    pthread_t *thread;
    int i = 0;

    thread = malloc(sizeof(pthread_t) * 100000);
    while (i < 1000)
    {
        pthread_create(&thread[i], NULL, hi, NULL);
        i++;
    }
    i = -1;
    while (++i < 1000)
        pthread_join(thread[i], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
