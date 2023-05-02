

CC		= cc

CFLAGS	= -Wall -Wextra -Werror


NAME = philo_bonus


BONUS   = main.c bonus_method.c bonus_utils.c bonus_errors.c bonus_routine.c

OBJB=$(BONUS:.c=.o)


all: ${NAME}

${NAME}:${OBJB}
	${CC} ${CFLAGS} -pthread -o ${NAME} ${BONUS}


%.o : %.c bonus_philo.h
	$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -rf  $(OBJB)

fclean: clean
	rm -rf  ${NAME}


re: fclean all

.PHONY: all clean fclean 