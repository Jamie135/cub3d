/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/24 16:19:52 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_data *data, int col, int height, int side, char direction)
{
	int	wall_start;
	int	wall_end;

	wall_start = HEIGHT / 2 - height / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = HEIGHT / 2 + height / 2;
	if (wall_end < 0)
		wall_end = HEIGHT - 1;
	for (int y = 0; y < HEIGHT; y++)
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
	int		height;

	for (int x = 0; x < WIDTH; x++)
	{
		camera_x = 2 * x / (double)(WIDTH)-1;
		ray_dir_x = data->player.dir.x + data->player.plane.x * camera_x;
		ray_dir_y = data->player.dir.y + data->player.plane.y * camera_x;
		printf("Raydir x(%f) y(%f)\n", ray_dir_x, ray_dir_y);
		printf("Angle: (%f)\n", atan2(ray_dir_y, ray_dir_x) * 180.0 / M_PI);
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
			if (data->map[map_x % data->len][map_y % data->height] == '1')
			{
				if (side == 0)
				{
					if (step_x == 1)
						direction = 'E'; // Wall facing east
					else
						direction = 'W'; // Wall facing west
				}
				else
				{
					if (step_y == 1)
						direction = 'S'; // Wall facing south
					else
						direction = 'N'; // Wall facing north
				}
				hit = 1;
			}
		}
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		height = (int)(HEIGHT / perp_wall_dist);
		draw_column(data, x, height, side, direction);
	}
}

int	key_hook(int keycode, t_data *data)
{
	double	move_speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	move_speed = 0.1;
	rot_speed = 0.05;
	// param is a pointer to mlx_ptr (mlx_ptr is not used in this example)
	// Handle arrow keys
	switch (keycode)
	{
	case 65362: // Up arrow key
		printf("Up arrow key pressed.\n");
		// if (data->map[(int) (data->player.position.x + data->player.dir.x
					// * move_speed)][(int) data->player.position.y] != '1')
		data->player.position.x += data->player.dir.x * move_speed;
		// if (data->map[(int) data->player.position.x][(int) (data->player.position.y
					// + data->player.dir.y * move_speed)] != '1')
		data->player.position.y += data->player.dir.y * move_speed;
		break ;
	case 65364: // Down arrow key
		printf("Down arrow key pressed.\n");
		// if (data->map[(int) (data->player.position.x - data->player.dir.x
					// * move_speed)][(int) data->player.position.y] != '1')
		data->player.position.x -= data->player.dir.x * move_speed;
		// if (data->map[(int) data->player.position.x][(int) (data->player.position.y
					// - data->player.dir.y * move_speed)] != '1')
		data->player.position.y -= data->player.dir.y * move_speed;
		break ;
	case 65361: // Left arrow key
	{
		printf("Left arrow key pressed.\n");
		old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(rot_speed)
			- data->player.dir.y * sin(rot_speed);
		data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y
			* cos(rot_speed);
		old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(rot_speed)
			- data->player.plane.y * sin(rot_speed);
		data->player.plane.y = old_plane_x * sin(rot_speed)
			+ data->player.plane.y * cos(rot_speed);
		break ;
	}
	case 65363: // Right arrow key
	{
		printf("Right arrow key pressed.\n");
		old_dir_x = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(-rot_speed)
			- data->player.dir.y * sin(-rot_speed);
		data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y
			* cos(-rot_speed);
		old_plane_x = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(-rot_speed)
			- data->player.plane.y * sin(-rot_speed);
		data->player.plane.y = old_plane_x * sin(-rot_speed)
			+ data->player.plane.y * cos(-rot_speed);
		break ;
	}
	default:
		break ;
	}
	printf("Position: x(%f) y(%f)\n", data->player.position.x,
			data->player.position.y);
	printf("Direction: x(%f) y(%f)\n", data->player.dir.x, data->player.dir.y);
	printf("Plane: x(%f) y(%f)\n", data->player.plane.x, data->player.plane.y);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
										&data->img.bpp,
										&data->img.len,
										&data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
	return (0);
}

void	render(t_data *data)
{
	render_player_init(data);
	printf("Height: %d\n", data->height);
	printf("Width: %d\n", data->len);
	for (int w = 0; w < data->height; w++)
	{
		for (int h = 0; h < data->len; h++)
		{
			printf("%c", data->map[w][h]);
		}
		printf("\n");
	}
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
	mlx_loop(data->mlx);
}
