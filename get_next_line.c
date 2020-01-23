/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-der <nvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:45:01 by nvan-der       #+#    #+#                */
/*   Updated: 2020/01/23 15:17:24 by nvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

static int		find_next_line(char *remainder)
{
	size_t i;

	i = 0;
	while (remainder[i] != '\0')
	{
		if (remainder[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1, char *temp, int value)
{
	int		size;
	int		i;
	char	*ret;

	if (value == 1)
		free(temp);
	i = 0;
	size = ft_strlen(s1);
	ret = malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (NULL);
	while (i < size)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char		*ft_strchr(const char *s, int c, char *remainder)
{
	size_t i;

	i = 0;
	free(remainder);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (ft_strdup(s + i + 1, NULL, 0));
		i++;
	}
	return (NULL);
}

static int		gnl_loop(int fd, char **line, char *temp, int ret)
{
	static char		buff[BUFFER_SIZE + 1];
	static char		*remainder;

	if (remainder != NULL)
		temp = ft_strdup(remainder, temp, 1);
	if (temp == NULL)
		return (-1);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		temp = ft_strjoin(temp, buff);
		remainder = ft_strchr(temp, '\n', remainder);
		if (remainder != NULL)
		{
			*line = ft_substr(temp, 0, find_next_line(temp));
			return ((*line == NULL) ? -1 : 1);
		}
	}
	*line = ft_substr(temp, 0, ft_strlen(temp));
	return ((*line == NULL) ? -1 : ret);
}

int				get_next_line(int fd, char **line)
{
	int		ret;
	char	*temp;

	temp = ft_strdup("", NULL, 0);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || temp == NULL || fd > OPEN_MAX)
	{
		if (temp)
			free(temp);
		return (-1);
	}
	ret = gnl_loop(fd, line, temp, 1);
	if (ret == -1)
		free(temp);
	return (ret);
}

int main(void)
{
	char *line;
	int fd;

	line = "";
	fd = open("test.txt", O_RDONLY);
	int i = 1;
	while (i > 0)
	{
		i = get_next_line(fd, &line);
		printf("%d = ", i);
		printf("%s\n", line);
	}
}
