/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:10:00 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/18 13:17:32 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//parse the identifiers and colors data to struct t_data until i = 6
//from i = 6, we start to parse each line of the map
//if (flag == i && line[0] != '\0') condition means that the parsing failed 
//at line i, in .cub file
int	check_data(t_data *data, char *line)
{
	static int	i = 0;
	int			flag;

	flag = i;
	if (i == 6)
	{
		if (check_map(data, line) == -1)
			return (-1);
		return (1);
	}
	if (!data->nord)
		i += parse_id(&data->nord, line, "NO");
	if (!data->south)
		i += parse_id(&data->south, line, "SO");
	if (!data->west)
		i += parse_id(&data->west, line, "WE");
	if (!data->east)
		i += parse_id(&data->east, line, "EA");
	if (!data->floor)
		i += parse_color(&data->floor, line, 'F');
	if (!data->ceiling)
		i += parse_color(&data->ceiling, line, 'C');
	if (flag == i && line[0] != '\0')
		return (-1);
	return (0);
}

//read the content of .cub file with get_next_line 
//and parse datas from each line with check_data
void	read_file(t_data *data, char *path)
{
	int			fd;
	int			gnl;
	char		*line;
	static int	flag = 0;

	gnl = -1;
	line = NULL;
	fd = open(path, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		free_message(data, "File does not exist");
	while (gnl != 0)
	{
		gnl = get_next_line(fd, &line);
		if (gnl == -1)
			free_message(data, "get_next_line failed");
		if (gnl >= 0)
		{
			if (check_data(data, line) == -1)
				flag = -1;
			free(line);
		}
	}
	if (flag == -1 || !data->map)
		free_message(data, "Wrong file format");
}

//check if it's a .cub file
void	check_file(t_data *data, char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (ft_strlen(file) < 4)
		free_message(data, ".cub is required");
	if (file[i--] != 'b')
		free_message(data, ".cub is required");
	if (file[i--] != 'u')
		free_message(data, ".cub is required");
	if (file[i--] != 'c')
		free_message(data, ".cub is required");
	if (file[i] != '.')
		free_message(data, ".cub is required");
}
