# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mdaan <mdaan@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/31 11:56:32 by mdaan         #+#    #+#                  #
#    Updated: 2021/01/08 14:15:38 by mdaan         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRCS	=	ft_memset.c				\
			ft_bzero.c				\
			ft_memcpy.c				\
			ft_memccpy.c			\
			ft_memmove.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strlen.c				\
			ft_strlcpy.c			\
			ft_strlcat.c			\
			ft_strchr.c				\
			ft_strrchr.c			\
			ft_strnstr.c			\
			ft_strncmp.c			\
			ft_atoi.c				\
			ft_isalpha.c			\
			ft_isdigit.c			\
			ft_isalnum.c			\
			ft_isascii.c			\
			ft_isprint.c			\
			ft_toupper.c			\
			ft_tolower.c			\
			ft_calloc.c				\
			ft_strdup.c				\
			ft_substr.c				\
			ft_strjoin.c			\
			ft_strtrim.c			\
			ft_split.c				\
			ft_itoa.c				\
			ft_strmapi.c			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c			\
			ft_get_unsig_len.c		\
			ft_get_len.c			\
			ft_get_hex_len.c		\
			ft_count_numbers.c		\
			ft_abs.c

SRCS_B	=	ft_lstnew.c				\
			ft_lstadd_front.c		\
			ft_lstsize.c			\
			ft_lstlast.c			\
			ft_lstadd_back.c		\
			ft_lstdelone.c			\
			ft_lstclear.c			\
			ft_lstiter.c			\
			ft_lstmap.c

OBJS	=	$(SRCS:.c=.o)
OBJS_B	=	$(SRCS_B:.c=.o)
LIBC	=	ar -rcs
RM		=	rm -f
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra

ifdef WITH_BONUS
RELEVANT_OBJS = $(OBJS) $(OBJS_B)
else
RELEVANT_OBJS = $(OBJS)
endif

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
