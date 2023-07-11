# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 00:05:10 by pbureera          #+#    #+#              #
#    Updated: 2023/07/11 00:05:10 by pbureera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D

SRC =	srcs/cub3d.c srcs/file.c srcs/free.c srcs/map.c srcs/map_valid.c \
		srcs/map_utils.c srcs/texture.c srcs/texture_utils.c srcs/edge.c\
		srcs/parse_data.c srcs/player.c  \
		# srcs/init_graphic.c srcs/exit.c

OBJ =	$(SRC:.c=.o)

CC =	clang 
FLAGS =	-Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c $(CC) $(FLAGS) -c $(SRC)

$(NAME):	libft/libft.a $(OBJ)
	$(CC) $(OBJ) libft/libft.a -o $(NAME) $(FLAGS)

libft/libft.a:
	cd libft && make && cd ..

clean:
	cd libft && make clean && cd ..
	rm -f $(OBJ)

fclean:	clean
	make fclean -C ./libft
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
