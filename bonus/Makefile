# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lshail <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 19:21:46 by lshail            #+#    #+#              #
#    Updated: 2023/05/02 19:21:49 by lshail           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= cc

CFLAGS	= -Wall -Wextra -Werror


NAME = philo_bonus


BONUS   = main.c bonus_method.c bonus_utils.c bonus_errors.c bonus_routine.c

OBJB=$(BONUS:.c=.o)


all: ${NAME}

${NAME}:${OBJB}
	${CC} ${CFLAGS} -pthread -o ${NAME} ${BONUS}


%.o : %.c bonus_philo.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf  $(OBJB)

fclean: clean
	rm -rf  ${NAME}


re: fclean all

.PHONY: all clean fclean 
