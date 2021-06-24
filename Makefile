NAME		=	cub3D

SRCS		=	src/main.c \
				src/init.c \
				src/parsing/check_info.c \
				src/parsing/check_map.c \
				src/parsing/parse.c \
				src/raycasting/move.c \
				src/raycasting/raycast.c \
				src/raycasting/render.c \
				src/utils/color.c \
				src/utils/errors.c \
				src/utils/hooks.c \
				src/utils/utils_mlx.c \
				src/utils/utils.c

HEADER		=	cub.h

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft.a
LIBFTDIR	=	./libft/

MLX			=	libmlx.a
MLXDIR		=	./mlx/

CC			=	gcc
CFLAGS		=	-Wall #-fsanitize=address -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C ./libft/
	make -C $(MLXDIR)
	$(CC) $(CFLAGS) $(LIBFTDIR)$(LIBFT) $(OBJS) -Llibft -Lmlx -lmlx -lz -framework OpenGL -framework Appkit -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -Imlx -c $< -o $@

clean:
	# find src -name "*.o" -type f -delete
	rm -f $(OBJS)
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX)

re: fclean all

ray:
	make
	./cub3D maps/map.cub

residential:
	make
	./cub3D maps/residential.cub

jungle:
	make
	./cub3D maps/jungle.cub

nontex:
	make
	./cub3D maps/nontex.cub

jungle2:
	make
	./cub3D maps/jungle2.cub

trip:
	make
	./cub3D maps/trip.cub

map2:
	make
	./cub3D maps/map2.cub

non:
	make
	./cub3D maps/mapss.cub

wrongarg:
	make
	./cub3D maps/mapss.cub hallo

debug:
	make
	# ./cub3D maps/map.cub
	./cub3D maps/valid_maps/valid_map_area_008.cub

invalid:
	make
	./cub3D maps/invalid_maps/invalid_map_area_014.cub

invalid_res:
	make
	./cub3D maps/invalid_maps/invalid_res_000.cub

.PHONY: all clean fclean re debug
