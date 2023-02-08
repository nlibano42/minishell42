/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:54:55 by jdasilva          #+#    #+#             */
/*   Updated: 2022/09/14 14:03:53 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
		return (0);
	ft_strlcpy(dst, s1, lens1 + 1);
	ft_strlcat(&dst[lens1], s2, lens2 + 1);
	return (dst);
}
