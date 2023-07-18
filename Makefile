# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 00:05:10 by pbureera          #+#    #+#              #
#    Updated: 2023/07/18 15:12:24 by pbureera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D

SRC =	srcs/cub3d.c srcs/file.c srcs/free.c srcs/map.c srcs/map_valid.c \
		srcs/map_utils.c srcs/texture.c srcs/texture_utils.c srcs/edge.c \
		srcs/parse_data.c srcs/player.c  \
		srcs/init_graphic.c srcs/exit.c srcs/rotation.c srcs/movements.c \
		srcs/movements_utils.c srcs/init_player.c

OBJ =	$(SRC:.c=.o)

CC =	clang 
FLAGS =	-Wall -Wextra -Werror -g
LIBMLX  =  -Llibft/ -lft \
-L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME):	$(OBJ)
	cd libft && make && cd ..
	cd minilibx-linux && make && cd ..
	@$(CC) $(FLAGS) $(HEADERS) -o $(NAME) $(OBJ) $(LIBMLX)

libft/libft.a:
	cd libft && make && cd ..

clean:
	cd libft && make clean && cd ..
	cd minilibx-linux && make clean && cd ..
	rm -rf $(OBJ)

fclean:	clean
	make fclean -C ./libft
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
