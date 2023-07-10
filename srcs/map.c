/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:02:28 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/10 21:02:28 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**realloc_map(t_data *data, char *line)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(sizeof(char *) * (height_map(data->map) + 2));
	if (!new)
		free_message(data, "map realoc failed");
	while (data->map[++i])
		new[i] = ft_strdup(data->map[i]);
	if (line)
		new[i] = ft_strdup(line);
	new[i + 1] = NULL;
	free_map(data);
	return (new);
}

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

int	is_map(char *line)
{
	static int	map_exist = 0;
	static int	map_end = 0;

	if (line[0] != '\0')
	{
		if (map_end)
			return (-1);
		map_exist = 1;
		return (1);
	}
	if (map_exist)
		map_end = 1;
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
}
