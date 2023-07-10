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
// # include <mlx.h>
# include "libft.h"
# include "get_next_line.h"
# include "struct.h"

/* map.c */
void	init_map(t_data *data, char *str);
int		check_map(t_data *data, char *line);
int		is_map(char *line);
void	parse_map(t_data *data, char *line);
char	**realloc_map(t_data *data, char *line);

/* map_utils.c */
int		height_map(char **map);
int		len_map(char **map);

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

/* free.c */
void	free_message(t_data *data, char *str);
void	free_texture(t_data *data);
void	free_map(t_data *data);

#endif
