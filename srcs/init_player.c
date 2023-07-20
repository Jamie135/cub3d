/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:01:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/18 14:50:19 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//initialize the player's orientation based on the given char c
void	player_direction(t_player *player, char c)
{
	if (c == 'S')
		init_rotation(player, 180, 0);
	else if (c == 'E')
		init_rotation(player, 90, 1);
	else if (c == 'W')
		init_rotation(player, 90, 0);
}

//calculates the player's x and y coordinates based on the given i and j
//initialize the player's direction vectors (up, down, right, left)
void	player_position(t_data *data, int i, int j)
{
	data->player.position.x = j * GRID + GRID / 2;
	data->player.position.y = i * GRID + GRID / 2;
	data->player.up.x = data->player.position.x;
	data->player.up.y = data->player.position.y - GRID * 0.1;
	data->player.down.x = data->player.position.x;
	data->player.down.y = data->player.position.y + GRID * 0.1;
	data->player.right.x = data->player.position.x + GRID * 0.1;
	data->player.right.y = data->player.position.y;
	data->player.left.x = data->player.position.x - GRID * 0.1;
	data->player.left.y = data->player.position.y;
}

//check if char c is present in str
int	is_present(char c, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
}

//go through the map with (i, j) until we found the player
//initialize the player's position and direction based on the map data
void	init_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->player.move = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->len)
		{
			if (is_present(data->map[i][j], "NSEW"))
			{
				player_position(data, i, j);
				player_direction(&data->player, data->map[i][j]);
			}
			j++;
		}
		i++;
	}
}
