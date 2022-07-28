#include "philo.h"

void print_fork(t_table *table, long id) {
    long timestamp = get_timestamp();

    printf("%ld %ld has taken a fork\n", timestamp, id + 1);
}

void print_eat(t_table *table, long id) {
    long timestamp = get_timestamp();

    printf("%ld %ld is eating\n", timestamp, id + 1);
}

void print_sleep(t_table *table, long id) {
    long timestamp = get_timestamp();

    printf("%ld %ld is sleeping\n", timestamp, id + 1);
}

void print_think(t_table *table, long id) {
    long timestamp = get_timestamp();

    printf("%ld %ld is thinking\n", timestamp, id + 1);
}

void print_died(t_table *table, long id) {
    long timestamp = get_timestamp();

    printf("%ld %ld is died\n", timestamp, id + 1);
}
