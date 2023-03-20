/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/20 20:28:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;

	if (check_init_params(argc, argv))
		return (1);
	g_shell.pid = 0;
	init_cmd(&cmd);
	init_env(&(cmd.env), env);
	ft_signal();
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
			if (check_spaces(cmd.readl) || is_quotes_opened(cmd.readl) \
				|| is_fin_redirection(cmd.readl) || is_open_pipe(cmd.readl) \
					|| line_parse(&cmd, cmd.env))
				continue ;
			else
			{
				count_pipe(&cmd, cmd.cmd_line);
				if (save_cmds(&cmd) == 0)
				{
			//		if ((!cmd.pipe->full_cmd && !ft_strcmp(cmd.pipe->redir->key, "readl")) || (cmd.pipe->full_cmd[0]) > 0)
					//if (cmd.pipe->full_cmd[0] )
					pipex_main(&cmd);
				}
				free_all(&cmd);
			}
			dup2(cmd.save_stdin, STDIN_FILENO);
			dup2(cmd.save_stdout, STDOUT_FILENO);
			close(cmd.save_stdin);
			close(cmd.save_stdout);
		}
	}
	return (0);
}
