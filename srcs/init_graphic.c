/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:39:34 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/18 14:31:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//this function takes a string of rgb color (e.g. 200,200,50)
//and split the value to int r, int g and int b
//then it returns an int representing color in rgb format
//return (r << 16 | g << 8 | b) combines the red, green, and blue values 
//into a single integer value
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
//printf("r: %i\n", r);

//load an XPM image file path and store it in struct img
//also store the width and height of the loaded image in struct texture
//then retrieves other fields of data about the loaded image and store
//the address data in addr from struct texture
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

//load and store XPM image data in struct img and struct texture
//assign an int representing the rgb value to text->ceiling and text->floor 
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
	text->ceiling = color_value(data->ceiling);
	text->floor = color_value(data->floor);
}
//printf("ceiling: %i\n", text->ceiling);

void	init_graphic(t_data *data)
{
	data->img.img = NULL;
	data->texture.nordw.img = NULL;
	data->texture.southw.img = NULL;
	data->texture.westw.img = NULL;
	data->texture.eastw.img = NULL;
	data->ray = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_file(data, "Mlx init failed");
	init_texture(data, data->mlx, &data->texture);
	init_player(data);
}
