CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rc

SRCS = test_main.c
SORT_SRCS = $(wildcard sort_tools/*.c)
OBJS = $(SRCS:.c=.o)
SORT_OBJS = $(SORT_SRCS:.c=.o)
LIBFT = utils/libft.a
NAME = test

all: $(NAME)

$(NAME): $(OBJS) $(SORT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS) $(SORT_OBJS): $(LIBFT)

$(LIBFT):
	make -C utils

clean:
	rm -f $(OBJS) $(SORT_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re