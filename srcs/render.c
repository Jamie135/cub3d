/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/19 19:19:24 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.len
		+ x * (data->img.bpp / 8));
	*(unsigned int *) dst = color;
}

void draw_column(t_data *data, int col, int height) {
	if (height != 0)
	{
		int wall_height = HEIGHT / height;

		int wall_start = HEIGHT / 2 - wall_height / 2;
		int wall_end = HEIGHT / 2 + wall_height / 2;

		int tex_x = 0; // texture x-coordinate, you can implement texture mapping for more realistic rendering

		for (int y = 0; y < HEIGHT; y++) {
			if (y < wall_start)
				ft_mlx_pixel_put(data, col, y, 0x6495ED); // Sky color
			else if (y >= wall_start && y <= wall_end)
				ft_mlx_pixel_put(data, col, y, 0x808080); // Wall color
			else
				ft_mlx_pixel_put(data, col, y, 0x008000); // Floor color
		}
	}
}

void	raycast(t_data *data)
{
	int	col;

	col = 0;
	while (col < WIDTH)
	{
		double camera_x = 2 * col / (double) WIDTH - 1;
		double ray_dir_x = data->player.dir.x + data->player.plane.x * camera_x;
		double ray_dir_y = data->player.dir.y + data->player.plane.y * camera_x;

		int map_x = (int) data->player.position.x;
		int map_y = (int) data->player.position.y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		double side_dist_x, side_dist_y;
		double perp_wall_dist;

		int step_x, step_y;
		int hit = 0;
		int side;

		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (data->player.position.x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.position.x) * delta_dist_x;
		}

		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (data->player.position.y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.position.y) * delta_dist_y;
		}

		while (!hit) {
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			if (data->map[map_x][map_y] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (map_x - data->player.position.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - data->player.position.y + (1 - step_y) / 2) / ray_dir_y;
		int height = (int) (HEIGHT / perp_wall_dist);
		draw_column(data, col, height);
		col++;
	}
}

void	render(t_data *data)
{
	data->player.position.x = 10.0;
	data->player.position.y = 10.0;
	data->player.dir.x = -1.0;
	data->player.dir.y = 0.0;
	data->player.plane.x = 0.0;
	data->player.plane.y = 0.66;
	data->img.window = mlx_new_window(data->mlx, HEIGHT, WIDTH, "cub3D");
	data->img.img = mlx_new_image(data->mlx, HEIGHT, WIDTH);
	data->img.addr = mlx_get_data_addr(data->img.img,
				&data->img.bpp,
				&data->img.len, &data->img.endian);
	// raycast(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
	mlx_loop_hook(data->mlx, &handle_no_event, &data->img);
	mlx_hook(data->img.window, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->img.window, 17, 1L << 17, &handle_cross, data);
	mlx_loop(data->mlx);
}
