/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:24:22 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 18:24:22 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//check if char player corresponds to a player
int	is_player(char player)
{
	if (player == 'N' || player == 'S'
		|| player == 'E' || player == 'W')
		return (1);
	return (0);
}

//checks if the coordination on the map is empty (denoted by a space character)
//if it is, it places the player character, otherwise it does not modify the map
int	place_player(char **map, int x, int y, char player)
{
	if (map[y][x] == ' ')
		return (1);
	map[y][x] = player;
	return (0);
}

//locate the position of the player in the map
int	locate_player(char **map)
{
	static int	y = 0;
	static int	x = 0;
	static char	player;

	if (y || x)
		return (place_player(map, x, y, player));
	while (map[y++])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				player = map[y][x];
				map[y][x] = '0';
				return (0);
			}
			x++;
		}
	}
	return (0);
}
