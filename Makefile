# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshail <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 15:22:43 by lshail            #+#    #+#              #
#    Updated: 2023/04/30 15:22:52 by lshail           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

NAME	= philo

SOURCE = main.c	 method.c	philo_utils.c	error_management.c  routine.c

all:	
	${CC} ${CFLAGS} -pthread -o ${NAME} ${SOURCE}

%.o : %.c philosophers.h
	$(CC) $(FLAGS) -c $< -o $@

bonus: all

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all

.PHONY: all clean fclean 
