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

CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=leak

NAME	= philo

SOURCE = main.c	 method.c	philo_utils.c	error_management.c  routine.c


OBJA=$(SOURCE:.c=.o)


all: ${NAME}

%.o : %.c philosophers.h
	$(CC) $(FLAGS) -c $< -o $@


${NAME}:${OBJA}
	${CC} ${CFLAGS} -pthread -o ${NAME} ${SOURCE}

clean:
	rm -rf $(OBJA) 

fclean: clean
	rm -rf ${NAME} 

re: fclean all

.PHONY: all clean fclean 
