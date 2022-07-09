#include "philo.h"

int usage() {
    printf("usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
    return 1;
}

bool check_arg(int argc, char **argv) {
    return argc == 5
        && is_number(argv[1])
        && is_number(argv[2])
        && is_number(argv[3])
        && is_number(argv[4]);
}

int main(int argc, char **argv) {
    if (!check_arg(argc, argv))
        return usage();
    printf("ok\n");
}
