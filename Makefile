# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 00:05:10 by pbureera          #+#    #+#              #
#    Updated: 2023/07/30 18:01:20 by tadiyamu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D
NAME_B =	cub3D_bonus

SRC =	srcs/cub3d.c srcs/file.c srcs/free.c srcs/map.c srcs/map_valid.c \
		srcs/map_utils.c srcs/texture.c srcs/texture_utils.c srcs/edge.c \
		srcs/parse_data.c srcs/player.c  \
		srcs/init_graphic.c srcs/exit.c srcs/rotation.c srcs/movements.c \
		srcs/movements_utils.c srcs/init_player.c \
		srcs/render.c srcs/render_player_init.c \
		srcs/render_map.c srcs/render_raycast.c srcs/render_raycast_utils.c \
		srcs/render_column.c \
		srcs/hooks/hooks_close.c srcs/texture_display.c

B_SRC =	srcs_bonus/cub3d_bonus.c srcs_bonus/file_bonus.c srcs_bonus/free_bonus.c srcs_bonus/map_bonus.c srcs_bonus/map_valid_bonus.c \
		srcs_bonus/map_utils_bonus.c srcs_bonus/texture_bonus.c srcs_bonus/texture_utils_bonus.c srcs_bonus/edge_bonus.c \
		srcs_bonus/parse_data_bonus.c srcs_bonus/player_bonus.c  \
		srcs_bonus/init_graphic_bonus.c srcs_bonus/exit_bonus.c srcs_bonus/rotation_bonus.c srcs_bonus/movements_bonus.c \
		srcs_bonus/movements_utils_bonus.c srcs_bonus/init_player_bonus.c \
		srcs_bonus/render_bonus.c srcs_bonus/render_player_init_bonus.c \
		srcs_bonus/render_map_bonus.c srcs_bonus/render_raycast_bonus.c srcs_bonus/render_raycast_utils_bonus.c \
		srcs_bonus/render_column_bonus.c \
		srcs_bonus/hooks/hooks_close_bonus.c srcs_bonus/texture_display_bonus.c

OBJ =	$(SRC:.c=.o)
B_OBJ =	$(B_SRC:.c=.o)

CC =	cc
LIBFT = ./libft/libft.a
MINILIBX = ./minilibx-linux/libmlx_Linux.a
FLAGS =	-Wall -Wextra -Werror -g
LIBMLX  =  -Llibft/ -lft \
-L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME):	$(OBJ) $(LIBFT) $(MINILIBX)
	@$(CC) -o $(NAME) $(OBJ) $(LIBMLX)

bonus: $(NAME_B)

${NAME_B}:	$(B_OBJ) $(LIBFT) $(MINILIBX)
	@$(CC) -o $(NAME_B) $(B_OBJ) $(LIBMLX)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	cd libft && make && cd ..

$(MINILIBX):
	cd minilibx-linux && make && cd ..

clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -rf $(OBJ)
	rm -rf $(B_OBJ)

fclean:	clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(NAME_B)

re:	fclean all

.PHONY:	all clean fclean re
