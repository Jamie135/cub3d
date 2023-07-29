/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:58:46 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/29 16:13:25 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//iterate over the map array and checks if '0' is surrounded by at least one ' '
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

//this function copies the elements from data->map to new map
//except when the elements is ' ', new[i + 1][j + 1] = tmp
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

//initializing every element in new map with character c
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

//allocates new map (2D array of characters) 
//the dimensions are determined by HEIGHT + 2 rows and data->len + 2 columns
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

//check the player placement, empty spaces and character validity by
//allocating a new map 
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
// int	i = 0;
// 	while (i < HEIGHT)
// 	{
// 		printf("%s\n", data->map[i]);
// 		i++;
// 	}
