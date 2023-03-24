/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:05:57 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/24 15:57:25 by nlibano-         ###   ########.fr       */
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

t_redir	init_redirection(char *file, char *type, char *key)
{
	t_redir	redir;

	redir.file = file;
	redir.key = key;
	redir.type = type;
	redir.fd = 0;
	return (redir);
}

int	init_minishell(int argc, char **argv, char **env, t_cmd	*cmd)
{
	if (check_init_params(argc, argv))
		return (1);
	g_shell.pid = 0;
	init_cmd(cmd);
	init_env(&(cmd->env), env);
	ft_signal();
	return (0);
}
