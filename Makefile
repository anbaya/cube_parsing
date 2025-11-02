NAME = cube
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBMLX = libft.a libmlx.a -lXext -lX11 -lm
SRCS = cube.c get_next_line.c first_steps_of_walls_parsing.c \
		reading.c tools_1.c tools_2.c tools_3.c tools_4.c tools_5.c \
		bridge.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBMLX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re