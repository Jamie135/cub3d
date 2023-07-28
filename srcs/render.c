/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:17:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/28 19:05:48 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_img *texture, int x, int y)
{
	int				offset;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	offset = ((y * (texture->len_line / 4)) + x) * 4;
	red = texture->addr[offset];
	green = texture->addr[offset + 1];
	blue = texture->addr[offset + 2];
	return ((red << 24) | (green << 16) | (blue << 8));
}

void	draw_column(t_data *data, int col, t_ray *ray)
{
	int		line_height;
	int		wall_start;
	int		wall_end;
	double	wall_x;
	int		y;
	int		tex_x;
	t_img	*wall;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	wall_start = HEIGHT / 2 - line_height / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = HEIGHT / 2 + line_height / 2;
	if (wall_end < 0)
		wall_end = HEIGHT - 1;
	wall = direction_wall(&data->texture, ray->direction);
	if (ray->side == 0)
		wall_x = data->player.position.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = data->player.position.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double) wall->width);
	if (ray->side == 0 && ray->dir.x > 0)
		tex_x = wall->width - tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_x = wall->width - tex_x - 1;
	double	step = 1.0 * wall->height / line_height;
	double	tex_pos = (wall_start - HEIGHT / 2 + line_height / 2) * step;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < wall_start)
			ft_mlx_pixel_put(data, col, y, data->texture.ceiling); // Sky color
		else if (y >= wall_start && y <= wall_end)
		{
			if (ray->direction == 'C')
				ft_mlx_pixel_put(data, col, y, 0xf94144);
			else if (ray->direction == 'O')
				ft_mlx_pixel_put(data, col, y, 0x02c39a);
			else
			{
				int	tex_y = (int) tex_pos % (wall->height);
				tex_pos += step;
				int color = get_texture_color(wall, tex_x, tex_y);
				ft_mlx_pixel_put(data, col, y, color);
			}
		}
		else
			ft_mlx_pixel_put(data, col, y, data->texture.floor); // Floor color
	}
}

void	raycast_hit_direction(t_ray *ray, int step_x, int step_y)
{
	ray->hit = 1;
	if (ray->side == 0)
	{
		if (step_x == 1)
			ray->direction = 'E';
		else
			ray->direction = 'W';
	}
	else
	{
		if (step_y == 1)
			ray->direction = 'S';
		else
			ray->direction = 'N';
	}
}

void	raycast(t_data *data)
{
	double	camera_x;
	t_ray	ray;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;

	for (int x = 0; x < WIDTH; x++)
	{
		camera_x = 2 * x / (double)(WIDTH) - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		map_x = (int) data->player.position.x;
		map_y = (int) data->player.position.y;
		double side_dist_x, side_dist_y;
		delta_dist_x = (ray.dir.x == 0) ? 1e30 : fabs(1 / ray.dir.x);
		delta_dist_y = (ray.dir.y == 0) ? 1e30 : fabs(1 / ray.dir.y);
		int step_x, step_y;
		if (ray.dir.x < 0)
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
		if (ray.dir.y < 0)
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
		ray.hit = 0;
		while (ray.hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				ray.side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				ray.side = 1;
			}
			char mapVal = data->map[map_x % data->height][map_y % data->len];
			if (mapVal == '1' || mapVal == 'C' || mapVal == 'O')
			{
				raycast_hit_direction(&ray, step_x, step_y);
				if (data->map[map_x % data->height][map_y % data->len] == 'C')
				{
					if (x % 5 == 0)
						ray.direction = 'C';
					else
						ray.hit = 0;
				}
				if (data->map[map_x % data->height][map_y % data->len] == 'O')
				{
					if (x % 5 == 0)
						ray.direction = 'O';
					else
						ray.hit = 0;
				}
			}
		}
		if (ray.side == 0)
			ray.perp_wall_dist = side_dist_x - delta_dist_x;
		else
			ray.perp_wall_dist = side_dist_y - delta_dist_y;
		draw_column(data, x, &ray);
	}
}

void	render_update_screen(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.len, &data->img.endian);
	raycast(data);
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->img.window, data->img.img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 32)
		action_door(data);
	else if (keycode == 1731)
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
	printf("Height: %d\n", data->height);
	printf("Width: %d\n", data->len);

	data->img.window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	render_update_screen(data);
	mlx_loop_hook(data->mlx, &handle_no_event, &data->img);
	mlx_hook(data->img.window, 2, 1L << 0, &handle_input, data);
	mlx_hook(data->img.window, 17, 1L << 17, &handle_cross, data);
	mlx_key_hook(data->img.window, &key_hook, data);
	mlx_hook(data->img.window, 6, 1L << 6, &rotation_mouse_move, data);
	mlx_loop(data->mlx);
}
