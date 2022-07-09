NAME = philo

OBJ_DIR += ./
SRCS += $(wildcard *.c)
OBJ_DIR += util/
SRCS += $(wildcard util/*.c)

OBJS = $(SRCS:%.c=obj/%.o)
OBJ_DIR := $(addprefix obj/, $(OBJ_DIR))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

HEADER = philo.h

CFLAGS = -g


$(NAME): $(OBJS)
	cc $(CFLAGS) -o $@ $(OBJS)

obj/%.o: %.c $(OBJ_DIR) $(HEADER)
	cc $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
