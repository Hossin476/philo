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
NAME_BONUS = philo_bonus

SOURCE = main.c	 method.c	philo_utils.c	error_management.c  routine.c
BONUS   = bonus/main.c bonus/bonus_method.c bonus/bonus_utils.c  \
bonus/bonus_errors.c bonus/bonus_routine.c

OBJA=$(SOURCE:.c=.o)
OBJB=$(BONUS:.c=.o)

all: ${NAME}
bonus: ${NAME_BONUS}
${NAME}:${OBJA}
	${CC} ${CFLAGS} -pthread -o ${NAME} ${SOURCE}

${NAME_BONUS}:${OBJB}
	$(CC) $(CFLAGS) -pthread -o $(NAME_BONUS) $(BONUS)

%.o : %.c philosophers.h
	$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -rf $(OBJA) $(OBJB)

fclean: clean
	rm -rf ${NAME} ${NAME_BONUS}

re: fclean all

.PHONY: all clean fclean 
