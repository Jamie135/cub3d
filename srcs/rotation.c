/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:47:05 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/26 15:47:38 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotation_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(ROTATION_SPEED)
		- data->player.dir.y * sin(ROTATION_SPEED);
	data->player.dir.y = old_dir_x * sin(ROTATION_SPEED) + data->player.dir.y
		* cos(ROTATION_SPEED);
	old_plane_x = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(ROTATION_SPEED)
		- data->player.plane.y * sin(ROTATION_SPEED);
	data->player.plane.y = old_plane_x * sin(ROTATION_SPEED)
		+ data->player.plane.y * cos(ROTATION_SPEED);
}

void	rotation_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-ROTATION_SPEED)
		- data->player.dir.y * sin(-ROTATION_SPEED);
	data->player.dir.y = old_dir_x * sin(-ROTATION_SPEED) + data->player.dir.y
		* cos(-ROTATION_SPEED);
	old_plane_x = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(-ROTATION_SPEED)
		- data->player.plane.y * sin(-ROTATION_SPEED);
	data->player.plane.y = old_plane_x * sin(-ROTATION_SPEED)
		+ data->player.plane.y * cos(-ROTATION_SPEED);
}

int	rotation_mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	int		delta_y;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	delta_x = x - data->player.prev_mouse.x;
	delta_y = y - data->player.prev_mouse.y;
	rot_speed = 0.00005;
	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-rot_speed * delta_x)
		- data->player.dir.y * sin(-rot_speed * delta_x);
	data->player.dir.y = old_dir_x * sin(-rot_speed * delta_x)
		+ data->player.dir.y * cos(-rot_speed * delta_x);
	old_plane_x = data->player.plane.x;
	data->player.plane.x = data->player.plane.x * cos(-rot_speed * delta_x)
		- data->player.plane.y * sin(-rot_speed * delta_x);
	data->player.plane.y = old_plane_x * sin(-rot_speed * delta_x)
		+ data->player.plane.y * cos(-rot_speed * delta_x);
	render_update_screen(data);
	data->player.prev_mouse.x = x;
	data->player.prev_mouse.x = y;
	return (0);
}
