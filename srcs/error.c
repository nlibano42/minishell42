/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:49:57 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/18 16:58:51 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void access_error(char *input)
{
	write(2, "minishell: ", 11);
	write(2, input, ft_strlen(input));
	write(2, ": Permission denied\n", 20);
}