/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:13:54 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/10 23:13:54 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//check if the first two characters in line is "NO" "SO" "WE" or "EA"
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
		{
			printf("line: %s\n", line + i);
			return (line + i);
		}
		i++;
	}
	return (NULL);
}

//check if the first two characters in line is "F" "C"
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
