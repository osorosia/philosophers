#include "philo.h"

void *start_routine(void *arg) {
    t_table *table = (t_table *)arg;
    long id = table->id;

    while (true) {
        if (table->philos[id]->next_act_kind == EAT) {
            action_eat(table, id);
        } else if (table->philos[id]->next_act_kind == SLEEP) {
            action_sleep(table, id);
        } else if (table->philos[id]->next_act_kind == THINK) {
            action_think(table, id);
        }
        sleep(1);
    }

    return NULL;
}
