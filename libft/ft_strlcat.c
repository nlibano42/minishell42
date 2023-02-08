/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:08:35 by jdasilva          #+#    #+#             */
/*   Updated: 2022/09/14 11:33:46 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	count;

	dstlen = ft_strlen(dst);
	count = dstlen + ft_strlen(src);
	if (dstlen >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (*src && dstsize - dstlen - 1)
		*(dst + dstlen++) = *src++;
	*(dst + dstlen) = '\0';
	return (count);
}
