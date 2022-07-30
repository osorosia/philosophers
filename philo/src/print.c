#include "philo.h"

void print_act(t_table *table, long id, t_action_kind act_kind) {
    const char *act_str[] = {
        "is eating",
        "is sleeping",
        "is thinking",
        "has taken a fork",
        "died",
    };
    long timestamp = get_timestamp() - table->start_timestamp;

    if (table->start_timestamp == 0 && id == 0) {
        table->start_timestamp = timestamp;
        timestamp = 0;
    }
    printf("%ld %ld %s\n", timestamp, id, act_str[act_kind]);
    table->philos[id]->prev_act_time = timestamp;
}
