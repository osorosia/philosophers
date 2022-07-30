#include "../philo.h"

void philo_set_next_act(t_philo *philo) {
    if (philo->next_act_kind == EAT)
        philo->next_act_kind = SLEEP;
    else if (philo->next_act_kind == SLEEP)
        philo->next_act_kind = THINK;
    else if (philo->next_act_kind == THINK)
        philo->next_act_kind = EAT;
}
