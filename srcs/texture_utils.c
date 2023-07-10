/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:07:53 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/11 06:07:53 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_xpm(int fd)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	s = "/* XPM */";
	c = 0;
	while (i < 9)
	{
		if (read(fd, &c, 1) != -1 && c == s[i])
			i++;
		else
		{
			close(fd);
			return (0);
		}
	}
	return (1);
}
