NAME = pipex
BNAME = pipex_bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = 	srcs/pipex.c \
		srcs/ft_strjoin.c \
        srcs/ft_strlcpy.c \
        srcs/ft_strlen.c \
        srcs/ft_split.c \
		srcs/ft_strstr.c \
		srcs/ft_strdup.c \
        srcs/utils.c \

BSRCS = srcs/pipex_bonus.c \
		srcs/ft_strjoin_bonus.c \
        srcs/ft_strlcpy_bonus.c \
        srcs/ft_strlen_bonus.c \
        srcs/ft_split_bonus.c \
		srcs/ft_strstr_bonus.c \
		srcs/ft_strdup_bonus.c \
        srcs/utils_bonus.c \

OBJS1 = $(SRCS:.c=.o)

OBJS2 = $(BSRCS:.c=.o)

%o: %c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS1)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

$(BNAME): $(OBJS2)
	$(CC) $(FLAGS) $(BSRCS) -o $(BNAME)

norm:
	norminette -R checkforbiddensourceheader $(SRCS)
	norminette -R checkdefine gnl/get_next_line.h
	norminette -R checkdefine includes/pipex.h includes/pipex_bonus.h

clean:
	@rm -f $(OBJS1) $(OBJS2)

fclean: clean
	@rm -f $(OBJS1) $(OBJS2)
	@rm -f pipex pipex_bonus

re:	fclean all

bonus: $(BNAME) all

.PHONY:	bonus clean fclean all re
