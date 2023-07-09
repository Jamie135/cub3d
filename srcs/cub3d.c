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
	if (argc < 2)
		printf("Error: .cub file is missing");
	else if (argc == 2)
	{
		if (is_cub(argv[1]))
			return (error_message(CUB));
	}
	else
		printf("Error: too many arguments");
}
