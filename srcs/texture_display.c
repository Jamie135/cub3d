/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:41:01 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/27 17:47:24 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//iterate through each pixel of the display ray
//calculate the appropriate color for each pixel in the wall texture
//and set the corresponding pixel's color in the 3D image frame
void	display_wall(t_frame *img, t_img *wall, t_display *display, double sy)
{
	int		i;
	int		j;
	int		p;
	t_coord	dim;

	i = 0;
	while (i < display->ray_h)
	{
		j = 0;
		dim.y = i;
		while (j < display->ray_l)
		{
			dim.x = j;
			//p = function that determines the color of a specific pixel in the wall texture
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
	return (NULL);
}

//calculates the position and scaling of the wall texture for a specific column 
//and then renders it on the screen
void	scale_wall(t_data *data, char direction, int hit, int perp_wall_dist)
{
	double		scale_y;
	t_img		*wall;
	t_display		*display;

	wall = direction_wall(&data->texture, direction);
	display->pos_wall.y = 0;
	display->pos_wall.x = hit * wall->width / (double)(GRID);
	display->ray_h = (double)(HEIGHT / perp_wall_dist);
	scale_y = (double)(wall->height) / display->ray_h;
	if (display->ray_h >= (double)(HEIGHT)) //this condition means the wall is taller than the screen, so the function performs additional adjustments to ensure the wall texture is displayed correctly within the visible portion of the screen
	{
		display->pos_wall.y = (display->ray_h - (double)HEIGHT) / 2 * scale_y;
		display->ray_h = HEIGHT;
	}
	display_wall(&data->img, wall, display, scale_y);
}
