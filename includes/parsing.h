/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:34:24 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/09 23:34:24 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

enum	e_errors
{
	CUB,
	FILE,
	PARSING,
	MALLOC,
	MULTIRES,
	BADSCREEN,
	MULTINO,
	BADNO,
	MULTISO,
	BADSO,
	MULTIWE,
	BADWE,
	MULTIEA,
	BADEA,
	MULTISPRITE,
	BADSPRITE,
	MULTIFLOOR,
	BADFLOOR,
	MULTICEIL,
	BADCEIL,
	MAP,
	CHARACTER,
	PARAMETER
};

/* parsing_utils.c  */
int		is_cub(char *str);

/* error_messages.c */
int		error_message(int n);

#endif