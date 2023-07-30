/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:01:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/30 16:00:53 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//initialize the player's orientation based on the given char c
void	player_direction(t_player *player, char c)
{
	player->direction = c;
}

//calculates the player's x and y coordinates based on the given i and j
//initialize the player's direction vectors (up, down, right, left)
void	player_position(t_data *data, int i, int j)
{
	data->player.position.x = i + 0.5;
	data->player.position.y = j + 0.5;
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
