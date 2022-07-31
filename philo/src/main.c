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
    if (pthread_mutex_init(&(table.print_mutex), NULL) != 0)
        error("pthread_mutex_init");

    // loop
    i = 0;
    while (i < rule.philo_num) {
        // forks
        if (pthread_mutex_init(&(table.forks[i]), NULL) != 0)
            error("pthread_mutex_init");
        i++;
    }

    // philos ----------------------------------------------------
    t_philo **philos = malloc(rule.philo_num * sizeof(t_philo *));

    i = 0;    
    while (i < rule.philo_num) {
        philos[i] = malloc(sizeof(t_philo));
        memset(philos[i], 0, sizeof(t_philo));
        philos[i]->id = i;
        philos[i]->table = &table;
        philos[i]->rule = &rule;
        i++;
    }
    
    table.philos = philos;

    // monitor ---------------------------------------------------
    t_monitor monitor;
    memset(&monitor, 0, sizeof(t_monitor));

    monitor.philos = philos;
    monitor.rule = &rule;
    monitor.table = &table;

    // start thread ----------------------------------------------
    // init threads
    pthread_t *philo_th = malloc(sizeof(pthread_t) * rule.philo_num);
    pthread_t monitor_th;

    // create threads
    i = 0;
    while (i < rule.philo_num) {
        pthread_create(&philo_th[i], NULL, philo_routine, philos[i]);
        i++;
    }
    pthread_create(&monitor_th, NULL, monitor_routine, &monitor);

    // join threads
    i = 0;
    while (i < rule.philo_num) {
        pthread_join(philo_th[i], NULL);
        i++;
    }
    printf("end\n");
}
