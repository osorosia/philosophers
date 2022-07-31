NAME = philo

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEP = $(SRC:src/%.c=obj/%.d)

OBJ_DIR = $(sort $(dir $(OBJ)))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

CFLAGS = -g
DEPFLAGS = -MMD -MP

ifeq ($(MAKECMDGOALS), debug)
	DEBUG = -D DEBUG
endif

$(NAME): $(OBJ)
	cc $(CFLAGS) $(DEBUG) -o $@ $(OBJ)

obj/%.o: src/%.c $(OBJ_DIR)
	cc $(CFLAGS) $(DEPFLAGS) $(DEBUG) -o $@ -c $<

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

debug:
	echo $(DEBUG)

test: all
	cd .test && bash test.sh

.PHONY: all clean fclean re
