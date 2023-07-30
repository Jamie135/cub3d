/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:44 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/30 15:58:09 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map(t_data *data)
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;

	delta_x = 150 / data->height;
	delta_y = 150 / data->len;
	map_x = 0;
	while (map_x < 150)
	{
		map_y = 0;
		while (map_y < 150)
		{
			if ((int)(map_x / delta_x) == (int) data->player.position.x
				&& (int)(map_y / delta_y) == (int) data->player.position.y)
				ft_mlx_pixel_put(data, map_x, map_y, 0xe63946);
			else if ((int)(map_x / delta_x) < data->height
					&& (int)(map_y / delta_y) < data->len
					&& data->map[(int)(map_x / delta_x)][
					(int)(map_y / delta_y)] == '1')
				ft_mlx_pixel_put(data, map_x, map_y, 0xe5e5e5);
			map_y++;
		}
		map_x++;
	}
}
