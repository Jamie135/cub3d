/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:48:51 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/23 16:29:44 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_coord
{
	double	x;
	double	y;
}			t_coord;

typedef struct s_img
{
	int		len_line;
	int		height;
	int		width;
	int		bpp;
	int		endian;
	int		*color;
	char	*addr;
	void	*img;
}				t_img;

typedef struct s_texture
{
	t_img	nordw;
	t_img	southw;
	t_img	westw;
	t_img	eastw;
	int		ceiling;
	int		floor;
}				t_texture;

typedef struct s_frame
{
	int				bpp;
	int				len;
	int				endian;
	int				move;
	void			*window;
	char			*addr;
	void			*img;
}		t_frame;

typedef struct s_player
{
	int		move;
	char	direction;
	t_coord	position;
	t_coord	dir;
	t_coord	plane;
}			t_player;

typedef struct s_data
{
	int			len;
	int			height;
	void		*mlx;
	char		**map;
	char		*nord;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	t_frame		img;
	t_texture	texture;
	t_player	player;
}				t_data;

#endif
