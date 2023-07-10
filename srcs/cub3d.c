/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:18:56 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/09 23:18:56 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub3d(char *name)
{
	int		fd;
	t_parse	parse;

	init_map(&parse);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (error_message(FILE));
	extract_cub(parse, fd);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error: wrong number of arguments", 2);
		return (-1);
	}
	init_map(&data, argv[1]);
}
