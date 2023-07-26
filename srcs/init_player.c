/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:01:11 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/26 15:17:45 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_direction(t_player *player, char c)
{
	player->direction = c;
}

//calculates the player's x and y coordinates based on the given i and j
//initialize the player's direction vectors (up, down, right, left)
void	player_position(t_data *data, int i, int j)
{
	data->player.position.x = i;
	data->player.position.y = j;
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
