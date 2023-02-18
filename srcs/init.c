/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:05:57 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/18 19:39:19 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->readl = NULL;
	cmd->cmd_line = NULL;
}

void	init_quotes_flags(t_quotes *quotes)
{
	quotes->flag_d = 0;
	quotes->flag_s = 0;
	quotes->join_str = NULL;
}
