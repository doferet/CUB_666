/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:16:04 by doferet           #+#    #+#             */
/*   Updated: 2025/03/03 16:29:54 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_next(char *s)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	line = malloc(sizeof(char) * ft_strlen(s) - i + 1);
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		line[j++] = s[i++];
	line[j] = '\0';
	free(s);
	return (line);
}

static char	*get_line(char *s)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc((sizeof(char)) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read_and_save(int fd, char *save)
{
	int		read_value;
	char	*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_value = 1;
	while (read_value != 0)
	{
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_value] = '\0';
		save = ft_strjoin_2(save, buf);
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = get_next(save);
	return (line);
}

/*#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int   main(int ac, char **av)
{
  char  *line; 
  int   fd;
  (void)ac;

  fd = open(av[1], O_RDONLY);
  line = get_next_line(fd);
  while (line)
  {
	printf("%s", line);
  	free(line);
  	line = get_next_line(fd);
  }
  close(fd);
  return (0);
}*/
