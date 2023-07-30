/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:44:29 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/12 15:19:17 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//realloc the size of data->map by adding +2 lenght
//and copy the string from data->map[i] to new[i]
char	**realloc_map(t_data *data, char *line)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(sizeof(char *) * (height_map(data->map) + 2));
	if (!new)
		free_message(data, "map realloc failed");
	while (data->map[++i])
		new[i] = ft_strdup(data->map[i]);
	if (line)
		new[i] = ft_strdup(line);
	new[i + 1] = NULL;
	free_map(data);
	return (new);
}

//parse each map line to **map variable in struct t_data
//i.e. copy the map from .cub file to **map
void	parse_map(t_data *data, char *line)
{
	if (!data->map)
	{
		data->map = malloc(sizeof(char *) * 2);
		if (!data->map)
			free_message(data, "map alloc failed");
		data->map[0] = ft_strdup(line);
		if (!data->map[0])
			free_message(data, "map[0] alloc failed");
		data->map[1] = NULL;
	}
	else
		data->map = realloc_map(data, line);
	data->height = height_map(data->map);
	data->len = len_map(data->map);
}

//this function return 0 until line[0] != '\0' 
//i.e. until we find the first map line after parsing the identifiers and rgb
//the condition if(map_line) is to check if we have '\0' between our map lines
int	is_map(char *line)
{
	static int	map_line = 0;
	static int	empty_line = 0;

	if (line[0] != '\0')
	{
		if (empty_line)
			return (-1);
		map_line = 1;
		return (1);
	}
	if (map_line)
		empty_line = 1;
	return (0);
}

int	check_map(t_data *data, char *line)
{
	if (is_map(line) == -1)
		return (-1);
	if (is_map(line) == 1)
		parse_map(data, line);
	return (1);
}

// int i = 0;
// 	while (data->map[i])
// 	{
// 		printf("map[%i]: %s\n", i, data->map[i]);
// 		i++;
// 	}
