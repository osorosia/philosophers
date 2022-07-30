#include "philo.h"

void *start_routine(void *arg) {
    t_table *table = (t_table *)arg;
    long id = table->id;

    while (true) {
        action_eat(table, id);
        sleep(1);
        action_sleep(table, id);
        sleep(1);
        action_think(table, id);
        sleep(1);
    }    
    return NULL;
}
