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

//go through data->floor which contains RGB values
//then the values are stored in the static int color array. 
//then the function checks if any of the color components exceeds 255
//and if rbg is between 0 and 2
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

//go through data->ceiling which contains RGB values
//then the values are stored in the static int color array. 
//then the function checks if any of the color components exceeds 255
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

//check if the floor and ceiling all have red, green and blue value
//and check if all three values are between 1 and 3 digits
void	check_rgb(t_data *data, char *str)
{
	int	i;
	int	digit;
	int	rgb;

	i = 0;
	digit = 0;
	rgb = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit++;
		else if (str[i] == ',')
		{
			if (digit < 1 || digit > 3)
				free_message(data, "Color error");
			digit = 0;
			rgb++;
		}
		else
			free_message(data, "Color wrong args");
		i++;
	}
	if (digit < 1 || digit > 3 || rgb != 2)
		free_message(data, "Color error");
}

//check if the path for the id is accessible
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

//check validity for colors and identifier's path 
void	check_texture(t_data *data)
{
	check_path(data);
	check_rgb(data, data->ceiling);
	check_rgb(data, data->floor);
	rgb_ceiling(data, 2);
	rgb_floor(data, 2);
}
