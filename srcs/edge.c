/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:58:46 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 16:58:46 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_zero(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i] && map[i + 1])
	{
		j = 1;
		while (map[i][j] && map[i][j + 1])
		{
			if (map[i][j] == '0'
				&& (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
				|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	flood_insert(t_data *data, char **new, char tmp)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
				new[i + 1][j + 1] = tmp;
			else
				new[i + 1][j + 1] = data->map[i][j];
			j++;
		}
		i++;
	}
}

//flood the character c in our new map
void	flood_assign(t_data *data, char **new, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT + 2)
	{
		j = 0;
		while (j < data->len + 2)
		{
			new[i][j] = c;
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
}

//alloc a new map with the height of 1003 and the width of data->len + 3
char	**flood_alloc(t_data *data)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (HEIGHT + 3));
	if (!new)
		return (NULL);
	new[HEIGHT + 2] = NULL;
	while (i < HEIGHT + 2)
	{
		new[i] = malloc(sizeof(char) * (data->len + 3));
		if (!new[i])
			return (NULL);
		new[i][data->len + 2] = '\0';
		i++;
	}
	return (new);
}

void	check_edge(t_data *data)
{
	char	**new;

	new = flood_alloc(data);
	if (!new)
		free_message(data, "new/tmp_map alloc failed");
	flood_assign(data, new, ' ');
	flood_insert(data, new, ' ');
	locate_player(new);
	free_map(data);
	data->map = new;
	if (check_zero(data->map) || locate_player(data->map))
		free_message(data, "Map is not closed");
}
