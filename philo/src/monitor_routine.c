#include "philo.h"

void *monitor_routine(void *arg) {
    t_table *table = (t_table *)arg;
    t_philo **philos = table->philos;
    t_rule *rule = table->rule;

    while (true) {
        long i = 0;
        bool eat_ok = false;
        if (rule->eat_count > 0)
            eat_ok = true;
        while (i < rule->philo_num) {
            pthread_mutex_lock(&table->eat_count_mutex[i]);
            if (philos[i]->eat_count < rule->eat_count)
                eat_ok = false;
            pthread_mutex_unlock(&table->eat_count_mutex[i]);

            pthread_mutex_lock(&table->eat_time_mutex[i]);
            if (philos[i]->prev_eat_time == 0 &&
                    get_timestamp() - table->start_time >= rule->die ||
                philos[i]->prev_eat_time > 0 &&
                    get_timestamp() - philos[i]->prev_eat_time >= rule->die) {
                pthread_mutex_lock(&table->print_mutex);
                table->finish = true;
                printf("%ld\t%ld died\n", get_timestamp() - table->start_time,
                       i + 1);
                pthread_mutex_unlock(&table->print_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->eat_time_mutex[i]);
            i++;
        }
        if (eat_ok) {
            pthread_mutex_lock(&table->print_mutex);
            table->finish = true;
            pthread_mutex_unlock(&table->print_mutex);
            return NULL;
        }
        usleep(10);
    }

    return NULL;
}
