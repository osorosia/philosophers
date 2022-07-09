#include "../philo.h"

bool is_number(char *str) {
    long i;

    i = 0;
    while ('0' <= str[i] && str[i] <= '9')
        i++;
    return (i > 0 && str[i] == '\0');
}
