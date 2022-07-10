#include "philo.h"

int usage() {
    printf("\nusage:\n");
    printf("  ./philo\n");
    printf("    [number_of_philosophers]\n");
    printf("    [time_to_die]\n");
    printf("    [time_to_eat]\n");
    printf("    [time_to_sleep]\n");
    printf("    ([number_of_times_each_philosopher_must_eat])\n");
    printf("    \n");
    return 1;
}

bool check_arg(int argc, char **argv) {
    return (argc == 5 || argc == 6) 
        && is_num(argv[1])
        && is_num(argv[2])
        && is_num(argv[3])
        && is_num(argv[4])
        && (argc != 6 || is_num(argv[5]));
}

int main(int argc, char **argv) {
    long i;

    if (!check_arg(argc, argv))
        return usage();

    // get params
    long philo_num = ft_atol(argv[1]);
    long die_time = ft_atol(argv[2]);
    long eat_time = ft_atol(argv[3]);
    long sleep_time = ft_atol(argv[4]);
    long times = -1;
    if (argc == 6)
        times = ft_atol(argv[5]);

    // init threads
    pthread_t *th = malloc(sizeof(pthread_t) * philo_num);
    if (th == NULL) {
        perror("malloc");
        return 1;
    }

    // create threads
    i = 0;
    while (i < philo_num) {
        printf("create\n");
        int ret = pthread_create(&th[i], NULL, start_routine, NULL);
        if (ret != 0) {
            perror("pthread_create");
            return 1;
        }
        usleep(10000);
        i++;
    }

    // join threads
    i = 0;
    while (i < philo_num) {
        pthread_join(th[i], NULL);
        i++;
    }
}
