# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/28 15:38:43 by mdaan         #+#    #+#                  #
#    Updated: 2021/05/17 20:11:41 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	cub
SRCS	=	src/main.c \
			src/parse.c \
			src/check_map.c \
			src/pixel.c \
			src/hook_action.c \
			src/move.c \
			src/utils.c \
			src/color.c \
			src/color_utils.c \
			src/printvar.c \
			src/render.c \
			src/errors.c \
			src/init.c \
			../libft/libft.a
			# $(shell find src -name '*.c')
			# read_till_end.c \
			# ../get_next_line/get_next_line.c
			# ../get_next_line/get_next_line_utils.c
CC		=	gcc
CFLAGS	=	-g -fsanitize=address #-Wall -Wextra # -Werror
MLX		=	mlxopengl
LIBFT	=	../libft/libft.a
LXFLAGS	=	-lmlx -framework OpenGL -framework AppKit

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -L $(MLX) $(CFLAGS) $(LXFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	find src -name "*.o" -type f -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

ray:
	make re
	./cub maps/map.cub

non:
	make re
	./cub maps/mapss.cub

wrongarg:
	make re
	./cub maps/mapss.cub hallo

debug:
	make re
	# ./cub maps/map.cub
	./cub maps/valid_maps/valid_map_area_008.cub

invalid:
	make re
	./cub maps/invalid_maps/invalid_map_area_014.cub

invalid_res:
	make re
	./cub maps/invalid_maps/invalid_res_000.cub

.PHONY: all clean fclean re debug
