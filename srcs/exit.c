/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:31:17 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 20:31:17 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_game(t_data *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->texture.eastw.img)
		mlx_destroy_image(data->mlx, data->texture.eastw.img);
	if (data->texture.westw.img)
		mlx_destroy_image(data->mlx, data->texture.westw.img);
	if (data->texture.southw.img)
		mlx_destroy_image(data->mlx, data->texture.southw.img);
	if (data->texture.nordw.img)
		mlx_destroy_image(data->mlx, data->texture.nordw.img);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	exit_window(t_data *data)
{
	if (data->img.window)
		mlx_destroy_window(data->mlx, data->img.window);
	data->img.window = NULL;
}

void	exit_file(t_data *data, char *str)
{
	exit_window(data);
	exit_game(data);
	free_message(data, str);
}
