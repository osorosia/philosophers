NAME = philo

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEP = $(SRC:src/%.c=obj/%.d)

OBJ_DIR = $(sort $(dir $(OBJ)))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

# CFLAGS = -g -fsanitize=thread
# CFLAGS = -g -fsanitize=address
DEPFLAGS = -MMD -MP

ifeq ($(MAKECMDGOALS), debug)
	DEBUG = -D DEBUG
endif

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

fclean: clean $(HEADER)
	rm -f $(NAME)

re: fclean all

debug:
	echo $(DEBUG)

test: all
	cd .test && bash test.sh

norm:
	norminette src | grep Error! || echo OK

.PHONY: all clean fclean re
