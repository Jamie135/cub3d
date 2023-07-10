/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:00:30 by pbureera          #+#    #+#             */
/*   Updated: 2023/03/08 02:00:30 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

int		get_next_line(int fd, char **line);
size_t	gnl_strlen(const char *str);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strndup(char *s);
char	*gnl_strjoin(const char *s1, const char *s2);
char	*gnl_strnchr(char *s, int c, int n);

#endif
