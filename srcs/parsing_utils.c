/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:31:32 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/09 23:31:32 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_cub(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i--] != 'b')
		return (1);
	if (str[i--] != 'u')
		return (1);
	if (str[i--] != 'c')
		return (1);
	if (str[i] != '.')
		return (1);
	return (0);
}
