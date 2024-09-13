NAME = philo
CC = cc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRC = 	main.c \
		initialization.c \
		utils.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

bonus: all

re: fclean all
