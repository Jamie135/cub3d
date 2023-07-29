/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:02:28 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/29 16:29:04 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//this function copies the elements from data->map to new map
//except when the elements is ' ', new[i + 1][j + 1] = '0'
void	insert_map(t_data *data, char **new)
{
	int	i;
	int	j;

	i = 0;
	while (new[i])
	{
		j = 0;
		while (new[i][j])
		{
			if (data->map[i + 1][j + 1] == ' ')
				new[i][j] = '0';
			else
				new[i][j] = data->map[i + 1][j + 1];
			j++;
		}
		i++;
	}
}

//assign char player to each element of the new map
void	assign_map(t_data *data, char **new, char player)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < data->len)
		{
			new[i][j] = player;
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
}

//allocate a 2D array representing a map and 
//initializes it with null-terminated strings
char	**alloc_map(t_data *data)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (HEIGHT + 1));
	if (!new)
		return (NULL);
	new[HEIGHT] = NULL;
	while (i < HEIGHT)
	{
		new[i] = malloc(sizeof(char) * (data->len + 1));
		if (!new[i])
			return (NULL);
		new[i][data->len] = '\0';
		i++;
	}
	return (new);
}

//allocate a new map and initialize the the map with '0'
void	create_map(t_data *data)
{
	char	**new;

	new = alloc_map(data);
	if (!new)
		free_message(data, "map alloc failed");
	assign_map(data, new, '0');
	insert_map(data, new);
	free_map(data);
	data->map = new;
}

//initialize various fields in struct data 
//check validity of a given file, its element, the map, etc
//then creates a map after everything is validated
void	init_map(t_data *data, char *str)
{
	data->map = NULL;
	data->nord = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	check_file(data, str);
	read_file(data, str);
	check_texture(data);
	check_element(data);
	check_edge(data);
	create_map(data);
}
// int	i = 0;
// 	while (i < HEIGHT)
// 	{
// 		printf("%s\n", data->map[i]);
// 		i++;
// 	}
