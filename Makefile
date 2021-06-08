NAME		=	cub

SRCS		=	src/main.c \
				src/parse.c \
				src/parse_checks.c \
				src/check_map.c \
				src/hooks.c \
				src/move.c \
				src/utils.c \
				src/color.c \
				src/color_utils.c \
				src/render.c \
				src/raycast.c \
				src/errors.c \
				src/init.c

OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft.a
LIBFTDIR	=	./libft/

MLX			=	libmlx.a
MLXDIR		=	./mlx/

CC			=	gcc
CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
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
	./cub maps/map.cub

jungle:
	make
	./cub maps/jungle.cub

jungle2:
	make
	./cub maps/jungle2.cub

trip:
	make
	./cub maps/trip.cub

map2:
	make
	./cub maps/map2.cub

non:
	make
	./cub maps/mapss.cub

wrongarg:
	make
	./cub maps/mapss.cub hallo

debug:
	make
	# ./cub maps/map.cub
	./cub maps/valid_maps/valid_map_area_008.cub

invalid:
	make
	./cub maps/invalid_maps/invalid_map_area_014.cub

invalid_res:
	make
	./cub maps/invalid_maps/invalid_res_000.cub

.PHONY: all clean fclean re debug
