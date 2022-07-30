#include "philo.h"


void action_eat(t_table *table, long id) {
    print_act(table, id, EAT);
}

void action_sleep(t_table *table, long id) {
    print_act(table, id, SLEEP);
}

void action_think(t_table *table, long id) {
    print_act(table, id, THINK);
}
