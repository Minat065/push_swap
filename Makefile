NAME = push_swap
TEST = test_push_swap
LIBFT_DIR = ./src/utils_libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes
AR = ar
ARFLAGS = rc

SRCS = $(wildcard src/*.c) \
	$(wildcard src/stack_basic/*.c) \
	$(wildcard src/operations/*.c) \
    $(wildcard src/sort/*.c)
TEST_SRCS = $(wildcard tests/*.c) \
	$(wildcard tests/basic_stack_test/*.c) \
	$(wildcard tests/op_test/*.c) \

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# .cから.oを作るルールを追加
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

test: $(TEST)

$(TEST): $(LIBFT) $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(TEST_OBJS) $(LIBFT) -o $(TEST)

debag: CFLAGS += -g
debag: re

valgrind: debag
	valgrind --leak-check=full ./$(TEST) 1 2 3 4 5

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test debag valgrind