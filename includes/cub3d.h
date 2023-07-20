/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:20:43 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/09 23:20:43 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "struct.h"

# define HEIGHT 640
# define WIDTH 400
# define GRID 10

/* map.c */
void	init_map(t_data *data, char *str);
void	create_map(t_data *data);
char	**alloc_map(t_data *data);
void	assign_map(t_data *data, char **new, char player);
void	insert_map(t_data *data, char **new);

/* map_valid.c */
int		check_map(t_data *data, char *line);
int		is_map(char *line);
void	parse_map(t_data *data, char *line);
char	**realloc_map(t_data *data, char *line);

/* map_utils.c */
int		height_map(char **map);
int		len_map(char **map);
void	check_element(t_data *data);
int		is_forbidden(char c);

/* file.c */
void	check_file(t_data *data, char *file);
void	read_file(t_data *data, char *path);
int		check_data(t_data *data, char *line);

/* parse_data.c */
int		parse_id(char **texture, char *line, char *id);
int		parse_color(char **texture, char *line, char c);
char	*check_id(char *id, char *line);
char	*check_color(char c, char *line);

/* texture.c */
void	check_texture(t_data *data);
void	check_path(t_data *data);
void	check_rgb(t_data *data, char *str);
int		rgb_ceiling(t_data *data, int rgb);
int		rgb_floor(t_data *data, int rgb);

/* texture_utils.c */
int		is_xpm(int fd);

/* edge.c */
void	check_edge(t_data *data);
char	**flood_alloc(t_data *data);
void	flood_assign(t_data *data, char **new, char c);
void	flood_insert(t_data *data, char **new, char tmp);
int		check_zero(char **map);

/* player.c */
int		locate_player(char **map);
int		place_player(char **map, int x, int y, char player);
int		is_player(char player);

/* init_graphic.c */
void	init_graphic(t_data *data);
void	init_texture(t_data *data, void *mlx, t_texture *text);
int		init_texture_valid(t_img *text, void *mlx, char *path);
int		color_value(char *str);

/* init_player.c */
void	init_player(t_data *data);
int		is_present(char c, char *str);
void	player_position(t_data *data, int i, int j);
void	player_direction(t_player *player, char c);

/* rotation.c */
void	init_rotation(t_player *p, double angle, int r);
void	rotate_clockwise(double angle, double *x, double *y, t_coord origin);
void	rotate_counter(double angle, double *x, double *y, t_coord origin);

/* movements.c */

/* movements_utils.c */
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

/* render.c */
void	render(t_data *data);

/* hooks/hooks_close.c */
int		handle_no_event(void);
int		handle_cross(t_data *data);
int		handle_input(int keysym, t_data *data);

/* exit.c */
void	exit_file(t_data *data, char *str);
void	exit_window(t_data *data);
void	exit_game(t_data *data);

/* free.c */
void	free_message(t_data *data, char *str);
void	free_texture(t_data *data);
void	free_map(t_data *data);
void	free_tabs(char **tab);

#endif
