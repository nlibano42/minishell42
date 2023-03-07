/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:29:18 by nlibano-          #+#    #+#             */
/*   Updated: 2022/07/27 17:59:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_nl(char *str, int *find, char **tmp, char *line)
{
	char	*s;

	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	if (ft_str_pos(str, 10) != -1)
	{
		s = ft_substr(str, 0, ft_str_pos(str, 10) + 1);
		if (!line)
			line = ft_strdup(s);
		else
			line = ft_strjoin(line, s);
		if (ft_str_pos(str, 10) < (int)ft_strlen(str) - 1)
			*tmp = ft_substr(str, ft_str_pos(str, 10) + 1, ft_strlen(str) + 1);
		free(s);
		*find = 1;
		return (line);
	}
	if (!line)
		line = ft_strdup(str);
	else
		line = ft_strjoin(line, str);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*tmp;
	char		*line;
	int			ret;
	int			find;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (ft_find_tmp_nl(&tmp, &line) == 1)
		return (line);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		line = ft_find_nl(buf, &find, &tmp, line);
		if (find == 1)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (line);
}

int	ft_find_tmp_nl(char **tmp, char **line)
{
	char	*buf;
	int		find;

	find = 0;
	if (*tmp)
	{
		if (ft_str_pos(*tmp, 10) < 0)
		{
			*line = ft_strdup(*tmp);
			free(*tmp);
			*tmp = NULL;
			return (0);
		}
		else
		{
			buf = ft_strdup(*tmp);
			*line = ft_find_nl(buf, &find, &(*tmp), *line);
			free(buf);
			return (find);
		}
	}
	return (0);
}	

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_size;

	i = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize <= i)
		return (dstsize + src_size);
	j = 0;
	while (src[j] != '\0' && ((i + 1) < dstsize))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
