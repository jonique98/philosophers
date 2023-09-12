#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *hi(void *a) {
    a = 0;

    pthread_mutex_lock(&mutex);


    printf("hi\n");

    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    return a;
}

int main() {
    pthread_t thread;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread, NULL, hi, NULL);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
