/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:31:09 by jdasilva          #+#    #+#             */
/*   Updated: 2022/09/14 17:01:18 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_numbs(long n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		size++;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_count_numbs(char *dst, long n, size_t size)
{
	if (n == 0)
		*dst = '0';
	if (n < 0)
	{
		*dst = '-';
		n *= -1;
	}
	while (n > 0)
	{
		*(dst + size--) = '0' + (n % 10);
		n /= 10;
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*dst;
	long	size;

	size = ft_numbs(n);
	dst = (char *)malloc(sizeof(char) * size + 1);
	if (!dst)
		return (0);
	*(dst + size--) = '\0';
	dst = ft_count_numbs(dst, n, size);
	return (dst);
}
