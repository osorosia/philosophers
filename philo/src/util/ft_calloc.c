#include "../philo.h"

void *ft_calloc(size_t count, size_t size) {
    void *p;

    p = malloc(count * size);
    if (p == NULL)
        return NULL;
    memset(p, 0, count * size);
    return p;
}
