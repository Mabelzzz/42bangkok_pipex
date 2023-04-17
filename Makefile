NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEAD = -Imlx

SRCS = 	ft_strjoin.c \
        ft_strlcpy.c \
        ft_strlen.c \
        ft_split.c \
		ft_strstr.c \
		ft_strdup.c \
        utils.c \
        pipex.c \

OBJS = $(SRCS:.c=.o)

%o: %c
	$(CC) $(FLAGS) $(HEAD) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

norm:
	norminette -R checkforbiddensourceheader $(SRCS)
	# norminette -R checkdefine so_long.h get_next_line/get_next_line.h

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(OBJS)
	@rm -f pipex

re:	fclean all

bonus: all

.PHONY:	bonus clean fclean all re
