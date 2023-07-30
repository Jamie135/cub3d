/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:41:01 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/30 15:34:15 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_frame *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr
			+ (x * img->len) + y * (img->bpp / 8)) = color;
}

int	color_pixel(t_img *text, t_display *disp, t_coord dim, double sy)
{
	int		i;
	int		j;
	int		h;
	int		l;

	i = (int)dim.y;
	j = (int)dim.x;
	h = (int)disp->pos_wall.y * text->len_line + (int)(i * sy) *text->len_line;
	l = (int)disp->pos_wall.x * (text->bpp / 8) + j * (text->bpp / 8);
	return (*(int *)(text->addr + l + h));
}

void	display_wall(t_frame *img, t_img *wall, t_display *display, double sy)
{
	int		i;
	int		j;
	int		color;
	t_coord	dim;

	i = 0;
	while (i < display->ray_h)
	{
		j = 0;
		dim.y = i;
		while (j < display->ray_l)
		{
			dim.x = j;
			color = color_pixel(wall, display, dim, sy);
			put_pixel(img, (int) display->pos_ray.y + i, \
						display->pos_ray.x + j, color);
			j++;
		}
		i++;
	}
}

t_img	*direction_wall(t_texture *t, char direction)
{
	if (direction == 'N')
		return (&t->nordw);
	else if (direction == 'S')
		return (&t->southw);
	else if (direction == 'W')
		return (&t->westw);
	else if (direction == 'E')
		return (&t->eastw);
	else if (direction == 'C')
		return (&t->eastw);
	else if (direction == 'O')
		return (&t->eastw);
	return (NULL);
}

void	scale_wall(t_data *data, char direction, int hit, int perp_wall_dist)
{
	double		scale_y;
	t_img		*wall;
	t_display	*display;

	wall = direction_wall(&data->texture, direction);
	display->pos_wall.y = 0;
	display->pos_wall.x = hit * wall->width / (double)(GRID);
	display->ray_h = (double)(HEIGHT / perp_wall_dist);
	scale_y = (double)(wall->height) / display->ray_h;
	if (display->pos_ray.y < 0)
		display->pos_ray.y = 0;
	if (display->ray_h >= (double)(HEIGHT))
	{
		display->pos_wall.y = (display->ray_h - (double)HEIGHT) / 2 * scale_y;
		display->ray_h = HEIGHT;
	}
	display_wall(&data->img, wall, display, scale_y);
}
