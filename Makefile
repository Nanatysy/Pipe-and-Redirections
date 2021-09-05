NAME = pipex

SRC =	ft_calloc.c \
		ft_split.c \
		ft_strdup.c \
		ft_strlen.c \
		error.c \
		path.c \
		main.c

OBJ = $(SRC:.c=.o)

HEADER = pipex.h

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAG) $^ -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG) $< -c

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all