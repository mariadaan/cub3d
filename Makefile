# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/28 15:38:43 by mdaan         #+#    #+#                  #
#    Updated: 2021/05/20 16:02:09 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	cub
SRCS	=	src/printvar.c \
			src/main.c \
			src/parse.c \
			src/check_map.c \
			src/pixel.c \
			src/hooks.c \
			src/move.c \
			src/utils.c \
			src/color.c \
			src/color_utils.c \
			src/render.c \
			src/raycast.c \
			src/errors.c \
			src/init.c \
			../libft/libft.a
CC		=	gcc
CFLAGS	=	-g -fsanitize=address -Wall -Wextra # -Werror
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

map2:
	make
	./cub maps/map2.cub

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
