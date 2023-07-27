/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:56:50 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/24 17:24:28 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	movements_forward(t_data *data)
{
	double	step_x;
	double	step_y;

	step_x = data->player.dir.x * MOVEMENT_SPEED;
	step_y = data->player.dir.y * MOVEMENT_SPEED;
	if (data->map[(int)(data->player.position.x + step_x)][
		(int) data->player.position.y] != '1')
		data->player.position.x += step_x;
	if (data->map[(int)data->player.position.x][
		(int)(data->player.position.y + step_y)] != '1')
		data->player.position.y += step_y;
}

void	movements_backward(t_data *data)
{
	double	step_x;
	double	step_y;

	step_x = data->player.dir.x * MOVEMENT_SPEED;
	step_y = data->player.dir.y * MOVEMENT_SPEED;
	if (data->map[(int)(data->player.position.x - step_x)][
		(int) data->player.position.y] != '1')
		data->player.position.x -= step_x;
	if (data->map[(int) data->player.position.x][
		(int)(data->player.position.y - step_y)] != '1')
		data->player.position.y -= step_y;
}

void	movements_left(t_data *data)
{
	double	step_x;
	double	step_y;

	step_x = -data->player.dir.y * MOVEMENT_SPEED;
	step_y = data->player.dir.x * MOVEMENT_SPEED;
	if (data->map[(int)(data->player.position.x + step_x)][
		(int) data->player.position.y] != '1')
		data->player.position.x += step_x;
	if (data->map[(int)data->player.position.x][
		(int)(data->player.position.y + step_y)] != '1')
		data->player.position.y += step_y;
}

void	movements_right(t_data *data)
{
	double	step_x;
	double	step_y;

	step_x = data->player.dir.y * MOVEMENT_SPEED;
	step_y = -data->player.dir.x * MOVEMENT_SPEED;
	if (data->map[(int)(data->player.position.x + step_x)][
		(int) data->player.position.y] != '1')
		data->player.position.x += step_x;
	if (data->map[(int)data->player.position.x][
		(int)(data->player.position.y + step_y)] != '1')
		data->player.position.y += step_y;
}
