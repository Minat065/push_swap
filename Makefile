# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 14:49:56 by mirokugo          #+#    #+#              #
#    Updated: 2025/03/26 16:54:09 by mirokugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft/includes

# Source files
SRCS_DIR = srcs
SRCS = 	$(SRCS_DIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors for output
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

# Compile libft first
$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# Compile push_swap
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking push_swap...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)push_swap compiled successfully!$(RESET)"

# Compile individual source files
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@echo "$(GREEN)Cleaning executables...$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

# Debug mode with additional flags
debug: CFLAGS += -g -DDEBUG=1
debug: re
	@echo "$(GREEN)Debug build completed!$(RESET)"

# Test target
test: $(NAME)
	@echo "$(GREEN)Running tests...$(RESET)"
	@bash tests/run_tests.sh

# Valgrind target for memory leak detection
valgrind: $(NAME)
	@echo "$(GREEN)Running Valgrind memory check...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 3 2 1

# Comprehensive Valgrind testing with various test cases
valgrind_full: $(NAME)
	@echo "$(GREEN)Running comprehensive Valgrind tests...$(RESET)"
	@bash tests/valgrind_test.sh

.PHONY: all clean fclean re debug test