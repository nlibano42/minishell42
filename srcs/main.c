/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/24 17:10:49 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_minishell(t_cmd *cmd)
{
	if (check_spaces(cmd->readl) || is_quotes_opened(cmd->readl) \
				|| is_fin_redirection(cmd->readl) || is_open_pipe(cmd->readl) \
					|| line_parse(cmd, cmd->env))
		return (1);
	return (0);
}

void	run_minishell(t_cmd *cmd)
{	
	count_pipe(cmd, cmd->cmd_line);
	if (save_cmds(cmd) == 0)
		pipex_main(cmd);
	free_all(cmd);
}

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;

	if (init_minishell(argc, argv, env, &cmd))
		return (1);
	while (1)
	{
		cmd.save_stdin = dup(STDIN_FILENO);
		cmd.save_stdout = dup(STDOUT_FILENO);
		cmd.readl = readline("Minishell $> ");
		add_history(cmd.readl);
		if (!cmd.readl)
			ft_exit(&cmd);
		if (ft_strlen(cmd.readl) > 0)
		{
			if (check_minishell(&cmd))
				continue ;
			else
				run_minishell(&cmd);
			close_stdin_stdout(&cmd);
		}
	}
	return (0);
}
