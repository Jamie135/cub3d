/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:16:03 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/07/31 17:50:36 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_player_init_ns(t_data *data)
{
	if (data->player.direction == 'N')
	{
		data->player.dir.x = 1.0;
		data->player.dir.y = 0.0;
		data->player.plane.x = 0.0;
		data->player.plane.y = -0.66;
	}
	else if (data->player.direction == 'S')
	{
		data->player.dir.x = -1.0;
		data->player.dir.y = 0.0;
		data->player.plane.x = 0.0;
		data->player.plane.y = 0.66;
	}
}

void	render_player_init_we(t_data *data)
{
	if (data->player.direction == 'W')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = 1.0;
		data->player.plane.x = 0.66;
		data->player.plane.y = 0.0;
	}
	else if (data->player.direction == 'E')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = -1.0;
		data->player.plane.x = -0.66;
		data->player.plane.y = 0.0;
	}
}

void	render_player_init(t_data *data)
{
	render_player_init_ns(data);
	render_player_init_we(data);
}
