/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldurmaz <aldurmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:32:48 by aldurmaz          #+#    #+#             */
/*   Updated: 2024/12/08 14:54:47 by aldurmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_read(int fd, char *putline)
{
	char	*buff;
	int		reader;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	reader = 1;
	while (!ft_strchr(putline, '\n') && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			free(putline);
			return (NULL);
		}
		buff[reader] = '\0';
		putline = ft_strjoin(putline, buff);
	}
	free(buff);
	return (putline);
}

char	*get_main_line(char *putline)
{
	int		i;
	char	*str;

	i = 0;
	if (!putline[i])
		return (NULL);
	while (putline[i] != 0 && putline[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
	{
		str[i] = putline[i];
		i++;
	}
	if (putline[i] == '\n')
	{
		str[i] = putline[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_put_remain(char *putline)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
		i++;
	if (!putline[i])
	{
		free (putline);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(putline) - i));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (putline[i + j] != '\0')
	{
		str[j] = putline[j + i];
		j++;
	}
	str[j] = '\0';
	free(putline);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*mainline;
	static char	*putline[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	putline[fd] = get_read(fd, putline[fd]);
	if (!putline[fd])
		return (NULL);
	mainline = get_main_line(putline[fd]);
	putline[fd] = get_put_remain(putline[fd]);
	return (mainline);
}
