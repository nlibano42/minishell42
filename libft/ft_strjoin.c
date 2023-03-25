/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:54:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/25 20:30:42 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!dst)
	{
		free(s1);
		free(s2);
		return (0);
	}
	ft_strlcpy(dst, s1, lens1 + 1);
	ft_strlcat(&dst[lens1], s2, lens2 + 1);
	free(s1);
	free(s2);
	return (dst);
}
