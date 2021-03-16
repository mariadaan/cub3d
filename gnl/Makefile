# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/31 11:56:32 by mdaan         #+#    #+#                  #
#    Updated: 2021/03/09 17:08:35 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	gnl.a

SRCS	=	get_next_line.c			\
			get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)
LIBC	=	ar -rcs
RM		=	rm -f
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra


all:		$(NAME)

$(NAME):	$(RELEVANT_OBJS)
			${LIBC} $(NAME) $(RELEVANT_OBJS)

%.o:		%.c
			$(CC) -c $(FLAGS) $< -o $@

bonus:
			$(MAKE) WITH_BONUS=1 all

clean:
			${RM} $(OBJS) $(OBJS_B)

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re %.o
