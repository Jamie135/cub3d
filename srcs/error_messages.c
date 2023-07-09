/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:39:40 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/09 23:39:40 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	message_3(int errornbr)
{
	if (errornbr == CUB)
		printf("Error: must be .cub file");
	if (errornbr == FILE)
		printf("Error: invalid file");
	return (0);
}

int	message_2(int errornbr)
{
	if (errornbr == BADSPRITE)
		printf("Error: can't open sprite textures");
	if (errornbr == MULTIFLOOR)
		printf("Error: multiple floor colors");
	if (errornbr == BADFLOOR)
		printf("Error: invalid floor colors");
	if (errornbr == MULTICEIL)
		printf("Error: multiple ceiling colors");
	if (errornbr == BADCEIL)
		printf("Error: invalid ceiling colors");
	if (errornbr == MAP)
		printf("Error: invalid map");
	if (errornbr == CHARACTER)
		printf("Error: invalid character in cub text");
	if (errornbr == PARAMETER)
		printf("Error: missing at least one parameter");
	if (errornbr == PARSING)
		printf("Error: there was an error while parsing");
	return (0);
}

int	message_1(int errornbr)
{
	if (errornbr == MULTIRES)
		printf("Error: multiple resolutions");
	if (errornbr == BADSCREEN)
		printf("Error: invalid screensize!");
	if (errornbr == MULTINO)
		printf("Error: multiple north textures");
	if (errornbr == BADNO)
		printf("Error: can't open north textures");
	if (errornbr == MULTISO)
		printf("Error: multiple south textures");
	if (errornbr == BADSO)
		printf("Error: can't open south textures");
	if (errornbr == MULTIWE)
		printf("Error: multiple west textures");
	if (errornbr == BADWE)
		printf("Error: can't open west textures");
	if (errornbr == MULTIEA)
		printf("Error: multiple east textures");
	if (errornbr == BADEA)
		printf("Error: can't open east textures");
	if (errornbr == MULTISPRITE)
		printf("Error: multiple sprite textures");
	return (0);
}

int	error_message(int n)
{
	message_1(n);
	message_2(n);
	message_3(n);
	return (0);
}
