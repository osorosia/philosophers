#include "philo.h"

void print_fork(long ts, long num) {
    printf("%ld %ld has taken a fork\n", ts, num);
}

void print_eat(long ts, long num) {
    printf("%ld %ld is eating\n", ts, num);
}

void print_sleep(long ts, long num) {
    printf("%ld %ld is sleeping\n", ts, num);
}

void print_think(long ts, long num) {
    printf("%ld %ld is thinking\n", ts, num);
}

void print_died(long ts, long num) {
    printf("%ld %ld is died\n", ts, num);
}
