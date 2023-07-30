/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:13:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/12 15:08:15 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//check if the first two characters in line are "NO" "SO" "WE" or "EA"
//if they are return the path of the id texture, ex: ./xpm/grass.xpm
char	*check_id(char *id, char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == id[0] && line[i + 1] == id[1])
		{
			found++;
			i++;
		}
		else if (found == 1 && line[i] != ' ')
			return (line + i);
		i++;
	}
	return (NULL);
}

//check if the first two characters in line is "F" or "C"
//if they are return the rgb value of the foor/ceiling, ex: 250,250,250
char	*check_color(char c, char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == c)
			found++;
		else if (found == 1 && line[i] != 32)
			return (line + i);
		i++;
	}
	return (NULL);
}

//parse the rgb value to texture[0], which is floor or ceiling in struct t_data
int	parse_color(char **texture, char *line, char c)
{
	char		*ptr;
	int			i;

	i = 0;
	ptr = check_color(c, line);
	if (!ptr)
		return (0);
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
		i++;
	*texture = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
	{
		texture[0][i] = ptr[i];
		i++;
	}
	texture[0][i] = '\0';
	while (ptr[i])
	{
		if (ptr[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

//parse the path of the identifiers to texture[0], 
//which is nord, south, west or east in struct t_data
int	parse_id(char **texture, char *line, char *id)
{
	char		*ptr;
	int			i;

	i = 0;
	ptr = check_id(id, line);
	if (!ptr)
		return (0);
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
		i++;
	*texture = malloc(sizeof(char) * i + 1);
	i = 0;
	while (ptr[i] && (ptr[i] > 32 && ptr[i] < 127))
	{
		texture[0][i] = ptr[i];
		i++;
	}
	texture[0][i] = '\0';
	while (ptr[i])
	{
		if (ptr[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
