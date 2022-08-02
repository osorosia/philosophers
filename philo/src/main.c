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

int dining_philos(t_table *table) {
    pthread_t *philo_th;
    pthread_t monitor_th;
    long i;
    int ret;

    philo_th = malloc(sizeof(pthread_t) * table->rule->philo_num);
    table->start_time = get_timestamp();
    i = 0;
    while (i < table->rule->philo_num) {
        ret = ft_pthread_create(&philo_th[i], NULL, philo_routine, table->philos[i]);
        if (ret != 0)
            return 1;
        i++;
    }
    ret = ft_pthread_create(&monitor_th, NULL, monitor_routine, table);
    if (ret != 0)
        return 1;
    ft_pthread_join(monitor_th, NULL);
    // printf("monitor join\n");
    i = 0;
    while (i < table->rule->philo_num) {
        ft_pthread_join(philo_th[i], NULL);
        // printf("philo[%ld] join\n", i);
        i++;
    }
    free(philo_th);
    return 0;
}

int main(int argc, char **argv) {
    t_table *table;
    int ret;

    if (!check_arg(argc, argv))
        return usage();
    table = table_new(argc, argv);
    if (table == NULL)
        return 1;
    return dining_philos(table);
}
