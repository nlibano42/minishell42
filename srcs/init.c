/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:05:57 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/28 00:40:47 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->readl = NULL;
	cmd->cmd_line = NULL;
	cmd->pipe = NULL;
	cmd->env = NULL;
	cmd->num_pipes = 0;
	cmd->redir = NULL;
}

void	init_quotes_flags(t_quotes *quotes)
{
	quotes->flag_d = 0;
	quotes->flag_s = 0;
	quotes->join_str = NULL;
}
