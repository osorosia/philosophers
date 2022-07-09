#include "../philo.h"

bool is_num(char *str) {
    long num;
    long i;

    num = 0;
    i = 0;
    while (ft_isdigit(str[i])) {
        num = num * 10 + str[i] - '0';
        if (num > INT_MAX)
            return false;
        i++;
    }
    return (i > 0 && str[i] == '\0');
}
