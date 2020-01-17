/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-der <nvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:44:59 by nvan-der       #+#    #+#                */
/*   Updated: 2020/01/17 19:51:11 by nvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*ret;

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

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*tdst;
	char		*tend;
	const char	*tsrc;

	tdst = dst;
	tend = dst + dstsize;
	tsrc = src;
	if (src == NULL)
		return (0);
	while (*tsrc != '\0' && tdst < tend)
	{
		*tdst = *tsrc;
		tdst++;
		tsrc++;
	}
	if (tdst < tend)
		*tdst = 0;
	else if (dstsize > 0)
		tdst[-1] = 0;
	while (*tsrc != '\0')
		tsrc++;
	return (tsrc - src);
}

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstl;
	size_t	srcl;

	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	if (!dstsize || dstsize < dstl)
		return (dstl + srcl - (dstl - dstsize));
	dstsize -= dstl;
	ft_strlcpy(dst + dstl, src, dstsize);
	return (dstl + srcl);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		sizestr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sizestr = ft_strlen((char *)s1);
	sizestr += ft_strlen((char *)s2);
	sizestr++;
	result = malloc(sizeof(char) * sizestr);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, sizestr);
	ft_strlcat(result, s2, sizestr);
	return (result);
}
