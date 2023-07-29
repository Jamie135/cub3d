/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:15:58 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/29 15:42:13 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tabs(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			if (data->map[i])
			{
				free(data->map[i]);
				data->map[i] = NULL;
			}
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

void	free_texture(t_data *data)
{
	if (data->nord)
		free(data->nord);
	if (data->south)
		free(data->south);
	if (data->west)
		free(data->west);
	if (data->east)
		free(data->east);
	if (data->ceiling)
		free(data->ceiling);
	if (data->floor)
		free(data->floor);
}

void	free_message(t_data *data, char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	free_texture(data);
	free_map(data);
	exit(1);
}
