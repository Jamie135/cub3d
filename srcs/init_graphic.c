/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:39:34 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/12 13:01:11 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//this function takes a string of rgb color (e.g. 200,200,50)
//to split the value to int r, int g and int b
//then it returns an int representing color in rgb format
int	color_value(char *str)
{
	char	**value;
	int		r;
	int		g;
	int		b;

	value = ft_split(str, ',');
	r = ft_atoi(value[0]);
	g = ft_atoi(value[1]);
	b = ft_atoi(value[2]);
	free_tabs(value);
	return (r << 16 | g << 8 | b);
}

int	init_texture_valid(t_img *text, void *mlx, char *path)
{
	text->img = mlx_xpm_file_to_image(mlx, path,
			&text->width, &text->height);
	if (!text->img)
		return (1);
	text->addr = mlx_get_data_addr(text->img, &text->bpp,
			&text->len_line, &text->endian);
	return (0);
}

void	init_texture(t_data *data, void *mlx, t_texture *text)
{
	if (init_texture_valid(&text->nordw, mlx, data->nord))
		exit_file(data, "NO text failed");
	if (init_texture_valid(&text->southw, mlx, data->south))
		exit_file(data, "SO text failed");
	if (init_texture_valid(&text->westw, mlx, data->west))
		exit_file(data, "WE text failed");
	if (init_texture_valid(&text->eastw, mlx, data->east))
		exit_file(data, "EA text failed");
	text->cieling = color_value(data->ceiling);
	text->floor = color_value(data->floor);
}

void	init_graphic(t_data *data)
{
	data->img.img = NULL;
	data->texture.nordw.img = NULL;
	data->texture.southw.img = NULL;
	data->texture.westw.img = NULL;
	data->texture.eastw.img = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_file(data, "Mlx init failed");
	init_texture(data, data->mlx, &data->texture);
}
