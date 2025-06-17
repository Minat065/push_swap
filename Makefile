# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by student           #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes

# Libft files
LIBFT_DIR = src/libft
LIBFT_SRCS = $(LIBFT_DIR)/ft_atoi.c \
             $(LIBFT_DIR)/ft_split.c \
             $(LIBFT_DIR)/ft_strlen.c \
             $(LIBFT_DIR)/ft_isdigit.c \
             $(LIBFT_DIR)/ft_putstr_fd.c \
             $(LIBFT_DIR)/ft_substr.c \
             $(LIBFT_DIR)/ft_strdup.c \
             $(LIBFT_DIR)/ft_strlcpy.c \
             $(LIBFT_DIR)/ft_memcpy.c \
             $(LIBFT_DIR)/ft_strncmp.c

# Source files organized by modules
CORE_SRCS = src/core/main.c \
            src/core/push_swap.c \
            src/core/error.c

PARSING_SRCS = src/parsing/parse.c \
               src/parsing/parse_utils.c

STACK_SRCS = src/stack/stack_init.c \
             src/stack/stack_utils.c

OPERATIONS_SRCS = src/operations/swap.c \
                  src/operations/push.c \
                  src/operations/rotate.c \
                  src/operations/reverse_rotate.c

ALGORITHMS_SRCS = src/algorithms/sort_small.c \
                  src/algorithms/sort_radix.c \
                  src/algorithms/sort_chunk.c \
                  src/algorithms/turkish_sort/turkish_sort.c \
                  src/algorithms/turkish_sort/turkish_cost.c \
                  src/algorithms/turkish_sort/turkish_moves.c \
                  src/algorithms/turkish_sort/turkish_utils.c

UTILS_SRCS = src/utils/utils.c \
             src/utils/utils2.c \
             src/utils/helpers.c \
             src/utils/target_finder.c \
             src/utils/target_finder2.c \
             src/utils/sort_utils.c

# All source files
SRCS = $(CORE_SRCS) $(PARSING_SRCS) $(STACK_SRCS) $(OPERATIONS_SRCS) \
       $(ALGORITHMS_SRCS) $(UTILS_SRCS) $(LIBFT_SRCS)

BONUS_SRCS = src/core/checker_bonus.c \
             $(PARSING_SRCS) \
             src/core/error.c \
             $(STACK_SRCS) \
             $(OPERATIONS_SRCS) \
             src/utils/checker_utils_bonus.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(LIBFT_DIR)/%.c=$(OBJ_DIR)/libft/%.o)
BONUS_OBJS = $(BONUS_SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Test files
TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/test_main.c \
            $(TEST_DIR)/test_parse.c \
            $(TEST_DIR)/test_operations.c \
            $(TEST_DIR)/test_sort_small.c \
            $(TEST_DIR)/test_sort_radix.c \
            $(TEST_DIR)/test_sort_chunk.c \
            $(TEST_DIR)/test_sort_turkish.c
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_NAME = run_tests

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully$(NC)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)○ Compiling $<$(NC)"

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)○ Compiling test $<$(NC)"

$(OBJ_DIR)/libft/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/libft
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)○ Compiling libft $<$(NC)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ $(BONUS_NAME) compiled successfully$(NC)"

test: $(TEST_NAME)
	@./$(TEST_NAME)

$(TEST_NAME): $(filter-out $(OBJ_DIR)/core/main.o, $(OBJS)) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/core/main.o, $(OBJS)) $(TEST_OBJS) -o $(TEST_NAME)
	@echo "$(GREEN)✓ Test suite compiled successfully$(NC)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✗ Object files removed$(NC)"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME) $(TEST_NAME)
	@echo "$(RED)✗ Executables removed$(NC)"

re: fclean all

# Development helpers
norm:
	@norminette src/ includes/

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re bonus test norm debug