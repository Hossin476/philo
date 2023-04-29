CC		= cc

CFLAGS	= -Wall -Wextra -Werror

NAME	= philo
NAME_BONUS = philo_bonus
SOURCE = main.c	 method.c	philo_utils.c	error_management.c  routine.c
BONUS   = main_bonus.c method_bonus.c philo_utils_bonus.c error_management_bonus.c routine_bonus.c

all:	
	${CC} ${CFLAGS} -pthread -o ${NAME} ${SOURCE}

%.o : %.c philosophers.h
	$(CC) $(FLAGS) -c $< -o $@

bonus:
	$(CC) $(CFLAGS) -pthread -o $(NAME_BONUS) $(BONUS)

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all

.PHONY: all clean fclean 