NAME = philo

SRCS = ft_atoi.c  ft_bzero.c  ft_calloc.c  ft_isdigit.c  ft_itoa.c  ft_putstr_fd.c  ft_strjoin.c  ft_strlen.c  ft_strncmp.c  message.c  p_utils.c  philo.c  utils.c

OBJS = $(SRCS:%.c=%.o)

CC = cc
CFLGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

