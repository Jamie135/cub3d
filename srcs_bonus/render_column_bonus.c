/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:15:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/30 17:22:46 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_color(t_img *texture, int x, int y)
{
	int				offset;

	offset = ((y * (texture->len_line / 4)) + x);
	return (((int *) texture->addr)[offset]);
}

void	render_column_texture(t_data *data, t_column *col, int x, int y)
{
	int	tex_y;
	int	color;

	tex_y = (int) col->tex_pos % (col->wall->height);
	col->tex_pos += col->step;
	color = get_texture_color(col->wall, col->tex_x, tex_y);
	ft_mlx_pixel_put(data, x, y, color);
}

void	render_column(t_data *data, t_ray *ray, t_column *col, int x)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < col->wall_start)
			ft_mlx_pixel_put(data, x, y, data->texture.ceiling);
		else if (y >= col->wall_start && y <= col->wall_end)
		{
			if (ray->direction == 'C')
				ft_mlx_pixel_put(data, x, y, 0xf94144);
			else if (ray->direction == 'O')
				ft_mlx_pixel_put(data, x, y, 0x02c39a);
			else
				render_column_texture(data, col, x, y);
		}
		else
			ft_mlx_pixel_put(data, x, y, data->texture.floor);
	}
}

void	draw_column(t_data *data, int x, t_ray *ray)
{
	t_column	col;

	col.line_height = (int)(HEIGHT / ray->perp_wall_dist);
	col.wall_start = HEIGHT / 2 - col.line_height / 2;
	if (col.wall_start < 0)
		col.wall_start = 0;
	col.wall_end = HEIGHT / 2 + col.line_height / 2;
	if (col.wall_end < 0)
		col.wall_end = HEIGHT - 1;
	col.wall = direction_wall(&data->texture, ray->direction);
	if (ray->side == 0)
		col.wall_x = data->player.position.y + ray->perp_wall_dist * ray->dir.y;
	else
		col.wall_x = data->player.position.x + ray->perp_wall_dist * ray->dir.x;
	col.wall_x -= floor(col.wall_x);
	col.tex_x = (int)(col.wall_x * (double) col.wall->width);
	if (ray->side == 0 && ray->dir.x > 0)
		col.tex_x = col.wall->width - col.tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		col.tex_x = col.wall->width - col.tex_x - 1;
	col.step = 1.0 * col.wall->height / col.line_height;
	col.tex_pos = (col.wall_start - HEIGHT / 2 + col.line_height / 2)
		* col.step;
	render_column(data, ray, &col, x);
}
