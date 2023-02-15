/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:18 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/15 21:52:41 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	check_quotes_flags(t_quotes *quotes, char c)
{
	if (c == '\'' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_s = 1;
	else if (c == '"' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_d = 1;
	else if (c == '\'' && quotes->flag_d == 1 && quotes->flag_s == 0)
		quotes->flag_d = 0;
	else if (c == '\'' && quotes->flag_d == 0 && quotes->flag_s == 1)
		quotes->flag_s = 0;
}