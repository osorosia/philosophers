NAME = philo

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEP = $(SRC:src/%.c=obj/%.d)

OBJ_DIR = $(sort $(dir $(OBJ)))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

CFLAGS = -g
DEPFLAGS = -MMD -MP

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ)

obj/%.o: src/%.c $(OBJ_DIR)
	cc $(CFLAGS) $(DEPFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

-include $(DEP)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean $(HEADER)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
