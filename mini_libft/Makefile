NAME = libft.a

SRCS = ft_split.c ft_memset.c ft_strdup.c ft_strjoin.c ft_substr.c \
       ft_strlen.c ft_strncmp.c ft_putstr_fd.c ft_strchr.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
