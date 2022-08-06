NAME = philo

SRC += $(addprefix src/, \
	action.c \
	main.c \
	monitor_routine.c \
	philo_routine.c \
	print.c \
	table.c \
	table1.c \
)
SRC += $(addprefix src/ft_pthread/, \
	ft_pthread_create.c \
	ft_pthread_join.c \
	ft_pthread_mutex_destroy.c \
	ft_pthread_mutex_lock.c \
	ft_pthread_mutex_unlock.c \
)
SRC += $(addprefix src/util/, \
	ft_atol.c \
	ft_calloc.c \
	ft_isdigit.c \
	get_timestamp.c \
	is_num.c \
)

OBJ = $(SRC:src/%.c=obj/%.o)
DEP = $(SRC:src/%.c=obj/%.d)

OBJ_DIR = $(sort $(dir $(OBJ)))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=thread
# CFLAGS += -g -fsanitize=address
DEPFLAGS = -MMD -MP

OS = $(shell uname)
ifeq ($(OS), Linux)
	LDFLAGS	= -pthread  -lpthread
endif

$(NAME): $(OBJ)
	cc $(CFLAGS) $(DEBUG) -o $@ $(OBJ) $(LDFLAGS)

obj/%.o: src/%.c $(OBJ_DIR)
	cc $(CFLAGS) $(DEPFLAGS) $(DEBUG) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

-include $(DEP)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	cd .test && bash test.sh

norm:
	norminette src | grep Error! || echo OK

.PHONY: all clean fclean re
