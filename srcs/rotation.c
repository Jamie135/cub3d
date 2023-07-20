/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:47:05 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/18 15:08:42 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//performs a rotation on a point (x, y) around the x-axis by an angle
//the direction is determined by r, where r = 1 indicates clockwise rotation
double	x_axis(double angle, double x, double y, int r)
{
	if (r)
		return (x * -cos(angle) + y * sin(angle));
	return (x * cos(angle) + y * -sin(angle));
}

//performs a rotation on a point (x, y) around the y-axis by an angle
//the direction is determined by r, where r = 1 indicates clockwise rotation
double	y_axis(double angle, double x, double y, int r)
{
	if (r)
		return (x * -sin(angle) + y * -cos(angle));
	return ((x * sin(angle) + y * cos(angle)));
}

//rotate (x, y) by the angle around the given origin point in counter clockwise
void	rotate_clockwise(double angle, double *x, double *y, t_coord origin)
{
	double	opos_x;
	double	opos_y;

	opos_x = *x - origin.x;
	opos_y = origin.y - *y;
	*x = x_axis(angle, opos_x, opos_y, 0);
	*x += origin.x;
	*y = y_axis(angle, opos_x, opos_y, 0);
	*y = origin.y - *y;
}

//rotate (x, y) by the angle around the given origin point in clockwise
void	rotate_counter(double angle, double *x, double *y, t_coord origin)
{
	double	opos_x;
	double	opos_y;

	opos_x = origin.x - *x;
	opos_y = origin.y - *y;
	*x = x_axis(angle, opos_x, opos_y, 1);
	*x += origin.x;
	*y = y_axis(angle, opos_x, opos_y, 1);
	*y += origin.y;
}

//initialize player's orientation by rotating its directional points 
//(up, down, right, and left)
//the rotation calculations of rotate_clockwise and rotate_counter functions 
//will determine how the player's orientation is updated
void	init_rotation(t_player *p, double angle, int r)
{
	if (!r)
	{
		rotate_clockwise(deg_to_rad(angle), &p->up.x, &p->up.y, p->position);
		rotate_clockwise(deg_to_rad(angle), &p->down.x, &p->down.y, p->position);
		rotate_clockwise(deg_to_rad(angle), &p->right.x, &p->right.y, p->position);
		rotate_clockwise(deg_to_rad(angle), &p->left.x, &p->left.y, p->position);
	}
	else
	{
		rotate_counter(deg_to_rad(angle), &p->up.x, &p->up.y, p->position);
		rotate_counter(deg_to_rad(angle), &p->down.x, &p->down.y, p->position);
		rotate_counter(deg_to_rad(angle), &p->right.x, &p->right.y, p->position);
		rotate_counter(deg_to_rad(angle), &p->left.x, &p->left.y, p->position);
	}
}
