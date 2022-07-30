#include "philo.h"


void action_eat(t_table *table, long id) {
    // print
    print_eat(table, id);
    // next action
    philo_set_next_act(table->philos[id]);
}

void action_sleep(t_table *table, long id) {
    // print
    print_sleep(table, id);
    // next action
    philo_set_next_act(table->philos[id]);
}

void action_think(t_table *table, long id) {
    // print
    print_think(table, id);
    // next action
    philo_set_next_act(table->philos[id]);
}
