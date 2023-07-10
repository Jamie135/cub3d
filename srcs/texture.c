/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:01:14 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 06:01:14 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb_floor(t_data *data, int rgb)
{
	static int	color[3];
	static int	i = 0;
	static int	index = 0;

	color[index] = ft_atoi(data->floor);
	while (data->floor[i])
	{
		if (data->floor[i] == ',')
		{
			index++;
			color[index] = ft_atoi(data->floor + i + 1);
		}
		i++;
	}
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		free_message(data, "Color value not accurate");
	if (rgb > 2 || rgb < 0)
		return (0);
	return (color[rgb]);
}

int	rgb_ceiling(t_data *data, int rgb)
{
	static int	color[3];
	static int	i = 0;
	static int	index = 0;

	color[index] = ft_atoi(data->ceiling);
	while (data->ceiling[i])
	{
		if (data->ceiling[i] == ',')
		{
			index++;
			color[index] = ft_atoi(data->ceiling + i + 1);
		}
		i++;
	}
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		free_message(data, "Color value not accurate");
	return (color[rgb]);
}

void	check_rgb(t_data *data, char *str)
{
	int	i;
	int	cpt;
	int	cpt_color;

	i = 0;
	cpt = 0;
	cpt_color = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			cpt++;
		else if (str[i] == ',')
		{
			if (cpt < 1 || cpt > 3)
				free_message(data, "Color error");
			cpt = 0;
			cpt_color++;
		}
		else
			free_message(data, "Color wrong args");
		i++;
	}
	if (cpt < 1 || cpt > 3 || cpt_color != 2)
		free_message(data, "Color error");
}

void	check_path(t_data *data)
{
	int	fd;

	fd = open(data->nord, O_RDONLY);
	if (fd == -1 || !is_xpm(fd))
		free_message(data, "NO File not found");
	close(fd);
	fd = open(data->south, O_RDONLY);
	if (fd == -1 || !is_xpm(fd))
		free_message(data, "SO File not found");
	close(fd);
	fd = open(data->west, O_RDONLY);
	if (fd == -1 || !is_xpm(fd))
		free_message(data, "WE File not found");
	close(fd);
	fd = open(data->east, O_RDONLY);
	if (fd == -1 || !is_xpm(fd))
		free_message(data, "EA File not found");
	close(fd);
}

void	check_texture(t_data *data)
{
	check_path(data);
	check_rgb(data, data->ceiling);
	check_rgb(data, data->floor);
	rgb_ceiling(data, 2);
	rgb_floor(data, 2);
}
