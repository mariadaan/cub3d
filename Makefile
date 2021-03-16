# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/28 15:38:43 by mdaan         #+#    #+#                  #
#    Updated: 2021/03/16 15:01:07 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	cub
SRCS	=	cub.c parse.c pixel.c hook_action.c move.c ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c ../libft/libft.a
CC		=	gcc
CFLAGS	=	-g #-Wall -Wextra -Werror
MLX		=	mlxopengl
LXFLAGS	=	-lmlx -framework OpenGL -framework AppKit

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -L $(MLX) $(CFLAGS) $(LXFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	make re
	./cub map.cub
