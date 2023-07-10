/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:05:08 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/10 22:05:08 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	len_map(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if ((size_t)len < ft_strlen(map[i]))
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

int	height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
