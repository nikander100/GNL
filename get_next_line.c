/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-der <nvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:45:01 by nvan-der       #+#    #+#                */
/*   Updated: 2020/01/17 22:24:25 by nvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	if (slen - start < len)
		len = slen - start;
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

static char		*ft_strchr(const char *s, int c, char *remainder)
{
	size_t i;

	i = 0;
	free(remainder);
	while (s[i] != 0)
	{
		if (s[i] == c)
			return (ft_strdup(s + i + 1));
		i++;
	}
	return (NULL);
}

static int		gnl_loop(int fd, char **line, char *temp, int ret)
{
	static char		buff[BUFFER_SIZE + 1];
	static char		*remainder;

	if (!remainder && !temp)
	{
		free(temp);
		temp = ft_strdup(remainder);
	}
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		temp = ft_strjoin(temp, buff);
		if (temp == NULL || ret == -1)
			return (-1);
		remainder = ft_strchr(temp, '\n', remainder);
		if (remainder != NULL)
		{
			*line = ft_substr(temp, 0, find_next_line(temp));
			return (1);
		}
	}
	*line = ft_substr(temp, 0, ft_strlen(temp));
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	int		ret;
	char	*temp;

	temp = ft_strdup("");
	if (fd < 0 || !line || BUFFER_SIZE < 1 || temp == NULL)
	{
		if (temp)
			free(temp);
		return (-1);
	}
	ret = gnl_loop(fd, line, temp, 1);
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
		free(line);
	}
}
