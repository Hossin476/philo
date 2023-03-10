CC		= cc

CFLAGS	= -Wall -Wextra -Werror

NAME	= philo

SOURCE = main.c	method.c	philo_utils.c	error_management.c\

all:	
	${CC} ${CFLAGS} -pthread -o ${NAME} ${SOURCE}

%.o : %.c philosophers.h
	$(CC) $(FLAGS) -c $< -o $@

bonus: all

clean:
	rm -f ${NAME}

fclean: clean

re: fclean all
