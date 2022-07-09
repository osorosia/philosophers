NAME = philo

SRCS = $(wildcard *.c)

HEADER = philo.h

OBJS = $(SRCS:%.c=obj/%.o)
OBJ_DIR = obj/.keep

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
