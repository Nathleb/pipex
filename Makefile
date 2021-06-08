# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nle-biha <nle-biha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 19:27:19 by nle-biha          #+#    #+#              #
#    Updated: 2021/06/08 15:18:13 by nle-biha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	pipex
CC		=	clang
FLAGS	=	-O3 -Wall -Wextra
SRCS	=	srcs/main.c srcs/pipex_utils.c	
INCS	=	$(addprefix includes/, pipex.h)
OBJS	=	$(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS) $(INCS)
	make -C libft
	$(CC) $(FLAGS) -I includes -o $(NAME) $(OBJS) -Llibft -lft

%.o: %.c $(INCS)
	$(CC) $(FLAGS) -I includes -c $< -o $@

clean:
	@make fclean -C libft
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
