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
    return (argc == 5 || argc == 6) && is_num(argv[1]) && is_num(argv[2]) &&
           is_num(argv[3]) && is_num(argv[4]) && (argc != 6 || is_num(argv[5]));
}

int main(int argc, char **argv) {
    long i;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%ld, %d\n", tv.tv_sec, tv.tv_usec);
    if (!check_arg(argc, argv))
        return usage();

    // rule ---------------------------------
    t_rule rule;
    rule.philo_num = ft_atol(argv[1]);
    rule.die = ft_atol(argv[2]);
    rule.eat = ft_atol(argv[3]);
    rule.sleep = ft_atol(argv[4]);
    rule.times = -1;
    if (argc == 6)
        rule.times = ft_atol(argv[5]);

    // table --------------------------------
    t_table table;
    memset(&table, 0, sizeof(table));

    // rule
    table.rule = &rule;
    // fork
    table.forks = malloc(rule.philo_num * sizeof(pthread_mutex_t));
    if (table.forks == NULL)
        error("malloc");
    // philos
    table.philos = malloc(rule.philo_num * sizeof(t_philo *));
    if (table.philos == NULL)
        error("malloc");

    // loop
    i = 0;
    while (i < rule.philo_num) {
        // forks
        int ret = pthread_mutex_init(&(table.forks[i]), NULL);
        if (ret != 0)
            error("pthread_mutex_init");
        // philos
        table.philos[i] = malloc(sizeof(t_philo));
        if (table.philos[i] == NULL)
            error("malloc");
        memset(table.philos[i], 0, sizeof(t_philo));
        i++;
    }

    // start thread ----------------------------------------------
    // init threads
    pthread_t *th = malloc(sizeof(pthread_t) * rule.philo_num);
    if (th == NULL)
        error("malloc");

    // create threads
    i = 0;
    while (i < rule.philo_num) {
        table.id = i;
        int ret = pthread_create(&th[i], NULL, start_routine, &table);
        if (ret != 0)
            error("pthread_create");
        usleep(1000);
        i++;
    }

    // join threads
    i = 0;
    while (i < rule.philo_num) {
        pthread_join(th[i], NULL);
        i++;
    }
    printf("end\n");
}
