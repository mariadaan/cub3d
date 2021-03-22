# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/28 15:38:43 by mdaan         #+#    #+#                  #
#    Updated: 2021/03/22 11:50:41 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	cub
SRCS	=	src/main.c \
			src/parse.c \
			src/pixel.c \
			src/hook_action.c \
			src/move.c \
			src/utils.c \
			src/color.c \
			src/color_utils.c \
			../libft/libft.a
			# $(shell find src -name '*.c')
			# read_till_end.c \
			# ../get_next_line/get_next_line.c
			# ../get_next_line/get_next_line_utils.c
CC		=	gcc
CFLAGS	=	-g -fsanitize=address #-Wall -Wextra # -Werror
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
	./cub cub3d_destroyer/valid_maps/valid_map_area_000.cub
	# ./cub map.cub

.PHONY: all clean fclean re debug
