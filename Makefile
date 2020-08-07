# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/02 15:19:28 by aimelda           #+#    #+#              #
#    Updated: 2020/07/20 19:30:27 by aimelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in

HDR		=	lemin.h

SRC		=	main.c			\
			parsing.c		\
			parse_rooms.c	\
			parse_links.c	\
			evaluating.c	\
			dinic.c			\
			print.c			\

LIBS	=	libft.a
LIBDIR	=	libft/
LIBPATH	=	$(addsuffix $(LIBS), $(LIBDIR))

CFLAGS	=	-g -Wall -Wextra -Werror

all: makelibs $(NAME)

$(NAME): $(SRC) $(HDR) $(LIBPATH)
	gcc $(CFLAGS) -o $@ $(SRC) -L $(LIBDIR) -lft

makelibs:
	make -C $(LIBDIR)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIBDIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBPATH)

re: fclean all

.PHONY: all clean fclean re makelibs