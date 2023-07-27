/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:41:01 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/26 21:41:01 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*direction_wall(t_texture *t, t_ray *ray)
{
	if (ray->walldirection == "N")
		return (&t->nordw);
	else if (ray->walldirection == "S")
		return (&t->southw);
	else if (ray->walldirection == "W")
		return (&t->westw);
	else if (ray->walldirection == "E")
		return (&t->eastw);
	return (NULL);
}

//calculates the position and scaling of the wall texture for a specific column 
//and then renders it on the screen
void	scale_wall(t_data *data, t_ray *ray)
{
	double		scale_y;
	t_img		*wall;

	wall = direction_wall(&data->texture, ray)
	
}
