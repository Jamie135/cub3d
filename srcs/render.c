/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/26 15:48:41 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_data *data, int col, int height, char direction)
{
	int	wall_start;
	int	wall_end;
	int	y;

	wall_start = HEIGHT / 2 - height / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = HEIGHT / 2 + height / 2;
	if (wall_end < 0)
		wall_end = HEIGHT - 1;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < wall_start)
			ft_mlx_pixel_put(data, col, y, data->texture.ceiling); // Sky color
		else if (y >= wall_start && y <= wall_end)
		{
			if (direction == 'N')
				ft_mlx_pixel_put(data, col, y, 0x264653);
			else if (direction == 'S')
				ft_mlx_pixel_put(data, col, y, 0x2a9d8f);
			else if (direction == 'E')
				ft_mlx_pixel_put(data, col, y, 0xe9c46a);
			else
				ft_mlx_pixel_put(data, col, y, 0xe76f51);
		}
		else
			ft_mlx_pixel_put(data, col, y, data->texture.floor); // Floor color
	}
}

char	raycast_hit_direction(int *hit, int step_x, int step_y, int side)
{
	*hit = 1;
	if (side == 0)
	{
		if (step_x == 1)
			return ('E');
		else
			return ('W');
	}
	else
	{
		if (step_y == 1)
			return ('S');
		else
			return ('N');
	}
}

void	raycast(t_data *data)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		hit;
	int		side;
	char	direction;

	for (int x = 0; x < WIDTH; x++)
	{
		camera_x = 2 * x / (double)(WIDTH)-1;
		ray_dir_x = data->player.dir.x + data->player.plane.x * camera_x;
		ray_dir_y = data->player.dir.y + data->player.plane.y * camera_x;
		map_x = (int)data->player.position.x;
		map_y = (int)data->player.position.y;
		double side_dist_x, side_dist_y;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		int step_x, step_y;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.position.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.position.x)
				* delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.position.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.position.y)
				* delta_dist_y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map[map_x % data->height][map_y % data->len] == '1')
				direction = raycast_hit_direction(&hit, step_x, step_y, side);
		}
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		draw_column(data, x, (int)(HEIGHT / perp_wall_dist), direction);
	}
}

void	render_update_screen(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.len, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 1731)
		movements_forward(data);
	else if (keycode == 1753)
		movements_backward(data);
	else if (keycode == 1730)
		movements_right(data);
	else if (keycode == 1738)
		movements_left(data);
	else if (keycode == 65361)
		rotation_left(data);
	else if (keycode == 65363)
		rotation_right(data);
	render_update_screen(data);
	return (0);
}

void	render(t_data *data)
{
	render_player_init(data);
	data->img.window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
										&data->img.bpp,
										&data->img.len,
										&data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
	mlx_loop_hook(data->mlx, &handle_no_event, &data->img);
	mlx_hook(data->img.window, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->img.window, 17, 1L << 17, &handle_cross, data);
	mlx_key_hook(data->img.window, &key_hook, data);
	mlx_hook(data->img.window, 6, 1L << 6, &rotation_mouse_move, data);
	mlx_loop(data->mlx);
}
