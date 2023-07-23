/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:47:05 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/23 16:30:12 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	rotatex(double angle, double x, double y, int r)
{
	if (r)
		return (x * -cos(angle) + y * sin(angle));
	return (x * cos(angle) + y * -sin(angle));
}

double	rotatey(double angle, double x, double y, int r)
{
	if (r)
		return (x * -sin(angle) + y * -cos(angle));
	return ((x * sin(angle) + y * cos(angle)));
}

void	rotatepoint(double angle, double *x, double *y, t_coord origin)
{
	double	opos_x;
	double	opos_y;

	opos_x = *x - origin.x;
	opos_y = origin.y - *y;
	*x = rotatex(angle, opos_x, opos_y, 0);
	*x += origin.x;
	*y = rotatey(angle, opos_x, opos_y, 0);
	*y = origin.y - *y;
}

void	rrotatepoint(double angle, double *x, double *y, t_coord origin)
{
	double	opos_x;
	double	opos_y;

	opos_x = origin.x - *x;
	opos_y = origin.y - *y;
	*x = rotatex(angle, opos_x, opos_y, 1);
	*x += origin.x;
	*y = rotatey(angle, opos_x, opos_y, 1);
	*y += origin.y;
}

void	init_rotation(t_player *p, double angle, int r)
{
	// if (!r)
	// {
	// 	rotatepoint(deg_to_rad(angle), &p->up.x, &p->up.y, p->position);
	// 	rotatepoint(deg_to_rad(angle), &p->down.x, &p->down.y, p->position);
	// 	rotatepoint(deg_to_rad(angle), &p->right.x, &p->right.y, p->position);
	// 	rotatepoint(deg_to_rad(angle), &p->left.x, &p->left.y, p->position);
	// }
	// else
	// {
	// 	rrotatepoint(deg_to_rad(angle), &p->up.x, &p->up.y, p->position);
	// 	rrotatepoint(deg_to_rad(angle), &p->down.x, &p->down.y, p->position);
	// 	rrotatepoint(deg_to_rad(angle), &p->right.x, &p->right.y, p->position);
	// 	rrotatepoint(deg_to_rad(angle), &p->left.x, &p->left.y, p->position);
	// }
}
