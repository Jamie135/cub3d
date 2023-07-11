/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:05:08 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/10 22:05:08 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_forbidden(char c)
{
	int			i;
	static char	str[] = " 01NSWE";

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W'
				|| str[i] == 'E')
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}

//check if we have other characters than "01NSWE" and if there's only 1 player
void	check_element(t_data *data)
{
	int	i;
	int	j;
	int	flag;
	int	player;

	i = 0;
	player = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			flag = is_forbidden(data->map[i][j]);
			if (flag == 1)
				free_message(data, "Forbidden element found");
			if (flag == -1)
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		free_message(data, "Wrong number of player in map");
}

int	len_map(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if ((size_t)len < ft_strlen(map[i]))
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

int	height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
