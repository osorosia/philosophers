#include "philo.h"

void *monitor_routine(void *arg) {
    t_monitor *monitor = (t_monitor *)arg;
    t_philo **philos = monitor->philos;
    t_rule *rule = monitor->rule;
    t_table *table = monitor->table;

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
                {
                    printf("%ld\t%ld died\n", get_timestamp() - table->start_time, i + 1);
                    long i = 0;
                    while (i < rule->philo_num) {
                        pthread_detach(monitor->philo_th[i]);
                        i++;
                    }
                }
                pthread_mutex_unlock(&table->print_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->eat_time_mutex[i]);

            i++;
        }
        usleep(10);
        if (eat_ok)
            break;
    }

    pthread_mutex_lock(&table->print_mutex);
    {
        long i = 0;
        while (i < rule->philo_num) {
            pthread_detach(monitor->philo_th[i]);
            i++;
        }
    }
    pthread_mutex_unlock(&table->print_mutex);
    return NULL;
}
