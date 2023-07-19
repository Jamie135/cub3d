/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/19 16:58:45 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	raycast(t_data *data)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;

	pos_x = 22;
	pos_y = 12;
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;

	time = 0;
	old_time = 0;

	for (int x = 0; x < WIDTH; x++)
	{
		double	camera_x = 2 * x / WIDTH - 1; //x-coordinate in camera space
		double	ray_dir_x = dir_x + plane_x * camera_x;
		double	ray_dir_y = dir_y + plane_y * camera_x;
	}
}

void	render(t_data *data)
{
	data->img.window = mlx_new_window(data->mlx, HEIGHT, WIDTH, "cub3D");
	mlx_hook(data->img.window, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->img.window, 17, 1L << 17, &handle_cross, data);
	mlx_loop(data->mlx);
}
