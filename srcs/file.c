/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:10:00 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/10 21:10:00 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_data(t_data *data, char *line)
{
	static int	i = 0;
	int			flag;

	flag = i;
	if (i == 6)
	{
		if (parse_map(data, line) == -1)
			return (-1);
		return (1);
	}
	if (!data->n_texture)
		i += parse_by_id(&data->n_texture, line, "NO");
	if (!data->s_texture)
		i += parse_by_id(&data->s_texture, line, "SO");
	if (!data->w_texture)
		i += parse_by_id(&data->w_texture, line, "WE");
	if (!data->e_texture)
		i += parse_by_id(&data->e_texture, line, "EA");
	if (!data->f_texture)
		i += parse_color(&data->f_texture, line, 'F');
	if (!data->c_texture)
		i += parse_color(&data->c_texture, line, 'C');
	if (flag == i && line[0] != '\0')
		return (-1);
	return (0);
}

void	read_file(t_data *data, char *path)
{
	int			fd;
	int			gnl;
	char		*line;
	static int	i = 0;

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
				i = -1;
			free(line);
		}
	}
	if (i == -1 || !data->map)
		free_message(data, "Wrong file format");
}

void	check_file(t_data *data, char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (ft_strlen(file) < 4)
		free_message(data, ".cub is required");
	if (str[i--] != 'b')
		free_message(data, ".cub is required");
	if (str[i--] != 'u')
		free_message(data, ".cub is required");
	if (str[i--] != 'c')
		free_message(data, ".cub is required");
	if (str[i] != '.')
		free_message(data, ".cub is required");
}
