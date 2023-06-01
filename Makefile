# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 01:18:39 by pnamwayk          #+#    #+#              #
#    Updated: 2023/06/02 01:18:40 by pnamwayk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	srcs/pipex.c \
		srcs/check_path.c \
		srcs/error.c \
		srcs/free.c \
		srcs/start_process.c \
		srcs/utils.c \
		srcs/ft_split.c \
		srcs/ft_strdup.c \
		srcs/ft_strjoin.c \
		srcs/ft_strlcpy.c \
		srcs/ft_strlen.c \
		srcs/ft_strstr.c \

BSRCS = bonus/pipex_bonus.c \
		bonus/ft_dup2.c \
		bonus/process.c \
		bonus/here_doc.c \
		bonus/utils_cmd.c \
		bonus/utils_free.c \
		bonus/utils_path.c \
		bonus/utils_error.c \
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

M_OBJS = $(SRCS:.c=.o)

B_OBJS = $(BSRCS:.c=.o)

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;33mGenerating pipex objects... %-10.10s\r" $@

all: $(NAME)
	@echo "\033[1;94m\n\nCompiling pipex (with the mandatory)...\n"

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME)

bonus: $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $(NAME)
	@echo "\033[1;94m\n\nCompiling pipex (with bonuses)..."

norm:
	norminette -R checkforbiddensourceheader $(SRCS) $(BSRCS)
	norminette -R checkdefine gnl/get_next_line.h
	norminette -R checkdefine includes/pipex.h includes/pipex_bonus.h
	@echo "\033[0;32m\n\nNorminette (with all files)..."

clean:
	@rm -fr $(M_OBJS) $(B_OBJS)

fclean: clean
	@rm -fr $(NAME)
	@rm -fr $(NAME).dSYM

re:	fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean norm re rebonus
