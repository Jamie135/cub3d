/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_display_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:41:01 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/30 17:23:02 by tadiyamu         ###   ########.fr       */
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
