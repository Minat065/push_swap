NAME = push_swap
TEST = test_push_swap
COMPREHENSIVE_TEST = comprehensive_test
PERFORMANCE_TEST = performance_test
TEST_500 = test_500_elements
LIBFT_DIR = ./src/utils_libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes
AR = ar
ARFLAGS = rc

# Source files (excluding main.c for tests)
SRCS = $(filter-out src/main.c, $(wildcard src/*.c)) \
	$(wildcard src/stack_basic/*.c) \
	$(wildcard src/operations/*.c) \
    $(wildcard src/sort/*.c)\
	$(wildcard src/utils/*.c)

# Test source files
LEGACY_TEST_SRCS = tests/test_main.c tests/unit/display_test.c
COMPREHENSIVE_TEST_SRCS = tests/comprehensive_test_main.c \
	tests/test_framework.c \
	tests/test_operations_silent.c \
	tests/unit/test_stack_operations.c \
	tests/unit/test_input_validation.c \
	tests/unit/test_sorting_algorithms.c

PERFORMANCE_TEST_SRCS = tests/performance_test_main.c \
	tests/test_framework.c \
	tests/test_operations_silent.c \
	tests/performance/test_performance.c

TEST_500_SRCS = tests/test_500_elements.c

OBJS = $(SRCS:.c=.o)
LEGACY_TEST_OBJS = $(LEGACY_TEST_SRCS:.c=.o)
COMPREHENSIVE_TEST_OBJS = $(COMPREHENSIVE_TEST_SRCS:.c=.o)
PERFORMANCE_TEST_OBJS = $(PERFORMANCE_TEST_SRCS:.c=.o)
TEST_500_OBJS = $(TEST_500_SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# .cから.oを作るルールを追加
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS) src/main.o
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) src/main.o $(LIBFT) -o $(NAME)

# Legacy test (original)
test: $(TEST)

$(TEST): $(LIBFT) $(OBJS) $(LEGACY_TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LEGACY_TEST_OBJS) $(LIBFT) -o $(TEST)

# Comprehensive TDD test suite
test-tdd: $(COMPREHENSIVE_TEST)

$(COMPREHENSIVE_TEST): $(LIBFT) $(OBJS) $(COMPREHENSIVE_TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(COMPREHENSIVE_TEST_OBJS) $(LIBFT) -o $(COMPREHENSIVE_TEST)

# Performance test suite
test-perf: $(PERFORMANCE_TEST)

$(PERFORMANCE_TEST): $(LIBFT) $(OBJS) $(PERFORMANCE_TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(PERFORMANCE_TEST_OBJS) $(LIBFT) -o $(PERFORMANCE_TEST)

# 500 elements test
test-500: $(TEST_500)

$(TEST_500): $(LIBFT) $(OBJS) $(TEST_500_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(TEST_500_OBJS) $(LIBFT) -o $(TEST_500)


debag: re

valgrind: debag
	valgrind --leak-check=full ./$(TEST) 1 2 3 4 5

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(LEGACY_TEST_OBJS) $(COMPREHENSIVE_TEST_OBJS) $(PERFORMANCE_TEST_OBJS) $(TEST_500_OBJS) src/main.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(TEST) $(COMPREHENSIVE_TEST) $(PERFORMANCE_TEST) $(TEST_500)

re: fclean all

.PHONY: all clean fclean re test test-tdd test-perf test-500 debag valgrind