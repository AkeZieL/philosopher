NAME = philo

SRCS = main.c init.c start.c rules.c utils.c check_error.c

OBJS_DIR = objs/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir objs

$(NAME):	$(OBJS)
	gcc $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
