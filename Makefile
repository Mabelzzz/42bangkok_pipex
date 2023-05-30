NAME = pipex
BNAME = pipex
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

BSRCS = bonus/pipex_bonus.c \
        bonus/utils_bonus.c \
		bonus/ft_strjoin_bonus.c \
        bonus/ft_strlcpy_bonus.c \
        bonus/ft_strlen_bonus.c \
		bonus/ft_strncmp_bonus.c \
        bonus/ft_split_bonus.c \
		bonus/ft_strstr_bonus.c \
		bonus/ft_strdup_bonus.c \
		bonus/ft_putstr_fd.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

OBJS1 = $(SRCS:.c=.o)

OBJS2 = $(BSRCS:.c=.o)

%o: %c
	$(CC) $(FLAGS) -c $< -o $@
	@printf "\033[0;33mGenerating pipex objects... %-10.10s\r" $@


$(NAME): $(OBJS1)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

$(BNAME): $(OBJS2)
	$(CC) $(FLAGS) $(BSRCS) -o $(BNAME)

norm:
	norminette -R checkforbiddensourceheader $(SRCS)
	norminette -R checkdefine gnl/get_next_line.h
	norminette -R checkdefine includes/pipex.h includes/pipex_bonus.h
	@echo "\033[0;32m\n\nNorminette (with all files)..."
	@echo "\033[1;94m\n\nNorminette (with all files)..."
# "\[\033[1;94m\]"

all: $(NAME)
	@echo "\033[1;94m\n\nCompiling pipex (with the mandatory)...\n"

clean:
	@rm -f $(OBJS1) $(OBJS2)

fclean: clean
	@rm -f $(OBJS1) $(OBJS2)
	@rm -f pipex

re:	fclean all bonus clean

bonus: $(BNAME)
		@echo "\033[1;94m\n\nCompiling pipex (with bonuses)..."

.PHONY:	bonus clean fclean all re
