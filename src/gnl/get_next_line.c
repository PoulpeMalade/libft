/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:17:08 by cberganz          #+#    #+#             */
/*   Updated: 2022/01/13 22:00:54 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*line_maker(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		line = (char *)malloc(i + 2 * sizeof(char));
	else
		line = (char *)malloc(i + 1 * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = save[i];
	if (line[i] != '\0')
		line[i + 1] = '\0';
	return (line);
}

static char	*ft_save_cleaner(char *save)
{
	char	*new_save;
	int		i;
	int		j;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = (char *)malloc(ft_strlen(save) - i * sizeof(char));
	if (!new_save)
		return (NULL);
	j = 0;
	i++;
	while (save[i + j])
	{
		new_save[j] = save[i + j];
		j++;
	}
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

static char	*ft_read(int fd, char *save)
{
	char	*buffer;
	int		read_return;

	buffer = (char *)malloc(42 + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	read_return = 1;
	while (no_newline_in(save) && read_return != 0)
	{
		read_return = read(fd, buffer, 42);
		if (read_return < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_return] = '\0';
		save = ft_join_gnl(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[257];
	char		*next_line;

	if (fd < 0 || fd > 256)
		return (NULL);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	next_line = line_maker(save[fd]);
	save[fd] = ft_save_cleaner(save[fd]);
	return (next_line);
}
