#include "../philo.h"

long ft_atol(char *str) {
    long num;
    long i;

    num = 0;
    i = 0;
    while (ft_isdigit(str[i]))
        num = num * 10 + str[i++] - '0';
    return num;
}
