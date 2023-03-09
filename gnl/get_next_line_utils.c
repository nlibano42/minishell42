/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:42:36 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/09 21:58:55 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_str_pos(char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
	}
	if (c == 0)
		return (i);
	return (-1);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\0')
		return (s2);
	if (s2[0] == '\0')
		return (s1);
	dst = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2)) + 1);
	if (!dst)
		return (NULL);
	gnl_strlcpy(dst, s1, gnl_strlen(s1) + 1);
	gnl_strlcat(dst, s2, (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	free(s1);
	return (dst);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (NULL);
	if (start > gnl_strlen(s))
		return (gnl_strdup(""));
	if (len > gnl_strlen(s))
		len = gnl_strlen(s);
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (dst == NULL)
		return (NULL);
	gnl_strlcpy(dst, &s[start], len + 1);
	return (dst);
}

char	*gnl_strdup(const char *s1)
{
	char	*dst;

	dst = (char *)malloc(gnl_strlen(s1) + 1);
	if (dst == NULL)
		return (NULL);
	gnl_strlcpy(dst, s1, gnl_strlen(s1) + 1);
	dst[gnl_strlen(s1)] = '\0';
	return (dst);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (src[src_size] != '\0')
		src_size++;
	if (dstsize == 0)
		return (src_size);
	i = 0;
	while (i < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i == dstsize)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (src_size);
}
