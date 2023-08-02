/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:29:52 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/08/02 11:04:51 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	raycast_hit_direction(t_ray *ray, int step_x, int step_y)
{
	ray->hit = 1;
	if (ray->side == 0)
	{
		if (step_x == 1)
			ray->direction = 'S';
		else
			ray->direction = 'N';
	}
	else
	{
		if (step_y == 1)
			ray->direction = 'E';
		else
			ray->direction = 'W';
	}
}

void	raycast_hit(t_data *data, t_ray *ray, int x)
{
	char	map_val;

	map_val = data->map[ray->map_x % data->height][
		ray->map_y % data->len];
	if (map_val == '1' || map_val == 'C' || map_val == 'O')
	{
		raycast_hit_direction(ray, ray->step_x, ray->step_y);
		if (data->map[ray->map_x % data->height][ray->map_y % data->len] == 'C')
		{
			if (x % 5 == 0)
				ray->direction = 'C';
			else
				ray->hit = 0;
		}
		if (data->map[ray->map_x % data->height][ray->map_y % data->len] == 'O')
		{
			if (x % 5 == 0)
				ray->direction = 'O';
			else
				ray->hit = 0;
		}
	}
}

void	raycast_dda(t_data *data, t_ray *ray, int x)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		raycast_hit(data, ray, x);
	}
}

void	raycast_step(t_data *data, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.position.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.position.x)
			* ray->delta_dist_x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.position.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.position.y)
			* ray->delta_dist_y;
	}
}

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ray.camera_x = 2 * x / (double)(WIDTH) - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * ray.camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * ray.camera_x;
		ray.map_x = (int) data->player.position.x;
		ray.map_y = (int) data->player.position.y;
		ray_delta_init(&ray);
		raycast_step(data, &ray);
		raycast_dda(data, &ray, x);
		if (ray.side == 0)
			ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
		draw_column(data, x, &ray);
	}
}
