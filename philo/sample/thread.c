#include "../src/philo.h"

int g = 0;

void *start_routine(void *data) {
    int *p = (int *)data;
    int val = *p;

    printf("thread_start_routine: val=%d\n", val);
    for (int i = 0; i < 10; i++) {
        g++;
        printf("thread: i=%d g=%d\n", i, g);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t th;
    void *th_ret;
    int num = 100;

    if (pthread_create(&th, NULL, start_routine, &num) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        g++;
        printf("main: i=%d g=%d\n", i, g);
        sleep(1);
    }

    if (pthread_join(th, &th_ret)) {
        perror("pthread_join");
        return 1;
    }

    return 0;
}
