#include "philo.h"

t_action_kind next_act(t_action_kind kind) {
    if (kind == EAT)
        return SLEEP;
    if (kind == SLEEP)
        return THINK;
    return EAT;
}

void action_eat(t_table *table, long id) {
    print_eat(table, id);
    table->philos[id]->next_act_kind =
        next_act(table->philos[id]->next_act_kind);
}

void action_sleep(t_table *table, long id) {
    print_sleep(table, id);
    table->philos[id]->next_act_kind =
        next_act(table->philos[id]->next_act_kind);
}

void action_think(t_table *table, long id) {
    print_think(table, id);
    table->philos[id]->next_act_kind =
        next_act(table->philos[id]->next_act_kind);
}
