/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-der <nvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:45:01 by nvan-der      #+#    #+#                 */
/*   Updated: 2021/05/17 11:30:35 by nvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			ret = ft_strdup(s + i + 1);
			if (ret == NULL)
			{
				free(s);
				return (0);
			}
			free(s);
			return (ret);
		}
		i++;
	}
	return (0);
}

int	ft_check_fd(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read_fd(char **temp, int fd, ssize_t ret)
{
	char	*buf;

	while (ret > 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			free(temp[fd]);
			return (NULL);
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buf);
			free(temp[fd]);
			return (NULL);
		}
		buf[ret] = '\0';
		temp[fd] = ft_strjoin(temp[fd], buf);
		if (temp[fd] == NULL)
			return (NULL);
		if (ft_check_fd(temp[fd]))
			break ;
	}
	return (temp[fd]);
}

int	ft_make_line(char **temp, char **line, int fd)
{
	int		i;

	i = 0;
	while (temp[fd][i] != '\n' && temp[fd][i] != '\0')
		i++;
	if (temp[fd][i] == '\n')
	{
		*line = ft_substr(temp[fd]);
		if (*line == NULL)
		{
			free(temp[fd]);
			return (-1);
		}
		temp[fd] = ft_strchr(temp[fd], '\n');
		if (temp[fd] == NULL)
			return (-1);
		return (1);
	}
	*line = ft_strdup(temp[fd]);
	free(temp[fd]);
	if (*line == NULL)
		return (-1);
	temp[fd] = 0;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	ssize_t		ret;
	static char	*temp[INT_MAX];

	ret = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	if (temp[fd] == NULL)
		temp[fd] = ft_strdup("");
	if (temp[fd] == NULL)
		return (-1);
	temp[fd] = ft_read_fd(temp, fd, ret);
	if (temp[fd] == NULL)
		return (-1);
	return (ft_make_line(temp, line, fd));
}

// TEST FUNCTION
// int	main(void)
// {
// 	char *line;
// 	int fd;

// 	line = "";
// 	fd = open("test.txt", O_RDONLY);
// 	int i = 1;
// 	while (i > 0)
// 	{
// 		i = get_next_line(fd, &line);
// 		printf("%d = ", i);
// 		printf("%s\n", line);
// 		free(line);
// 	}
// }
