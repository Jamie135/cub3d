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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong number of arguments", 2);
		return (-1);
	}
	init_map(&data, argv[1]);
	init_graphic(&data);
	render(&data);
	exit_game(&data);
	free_texture(&data);
	free_map(&data);
}
