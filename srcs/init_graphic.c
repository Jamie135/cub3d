/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:49:15 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 19:49:15 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}
