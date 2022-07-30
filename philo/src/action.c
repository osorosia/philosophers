#include "philo.h"


void action_eat(t_table *table, long id) {
    print_act(table, id, EAT);
    philo_set_next_act(table->philos[id]);
}

void action_sleep(t_table *table, long id) {
    print_act(table, id, SLEEP);
    philo_set_next_act(table->philos[id]);
}

void action_think(t_table *table, long id) {
    print_act(table, id, THINK);
    philo_set_next_act(table->philos[id]);
}
