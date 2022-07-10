#ifndef PHILO_H
#define PHILO_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

// print.c
void print_fork(long ts, long num);
void print_eat(long ts, long num);
void print_sleep(long ts, long num);
void print_think(long ts, long num);
void print_died(long ts, long num);

//
// util
//
long ft_atol(char *str);
bool ft_isdigit(char c);
bool is_num(char *str);

#endif
