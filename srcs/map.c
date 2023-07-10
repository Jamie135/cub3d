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
}
