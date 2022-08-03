#include "philo.h"

void set_finish(t_table *table) {
    ft_pthread_mutex_lock(&table->print_mutex);
    table->finish = true;
    ft_pthread_mutex_unlock(&table->print_mutex);
}

long get_eat_count_of_philo(t_table *table, long id) {
    long eat_count;

    ft_pthread_mutex_lock(&table->eat_count_mutex[id]);
    eat_count = table->philos[id]->eat_count;
    ft_pthread_mutex_unlock(&table->eat_count_mutex[id]);
    return (eat_count);
}

bool check_philo_died(t_table *table, long id) {
    bool is_died;

    ft_pthread_mutex_lock(&table->eat_time_mutex[id]);
    if (table->philos[id]->prev_eat_time == 0 &&
            get_timestamp() - table->start_time >= table->rule->die ||
        table->philos[id]->prev_eat_time > 0 &&
            get_timestamp() - table->philos[id]->prev_eat_time >=
                table->rule->die)
    {
        set_finish(table);
        is_died = true;
    }
    ft_pthread_mutex_unlock(&table->eat_time_mutex[id]);
    return (is_died);
}

void *monitor_routine(void *arg) {
    t_table *table = (t_table *)arg;
    t_philo **philos = table->philos;
    t_rule *rule = table->rule;

    while (true) {
        long i = 0;
        bool eat_ok = true;
        while (i < rule->philo_num) {
            if (rule->eat_count < 0 ||
                get_eat_count_of_philo(table, i) < rule->eat_count)
                eat_ok = false;
            if (check_philo_died(table, i)) {
                printf("%ld\t%ld died\n", get_timestamp() - table->start_time, i + 1);
                return (NULL);
            }
            i++;
        }
        if (eat_ok) {
            set_finish(table);
            return NULL;
        }
        usleep(10);
    }
    return NULL;
}
