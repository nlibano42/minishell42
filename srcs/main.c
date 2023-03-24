/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/24 15:52:27 by nlibano-         ###   ########.fr       */
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
					pipex_main(&cmd);
				free_all(&cmd);
			}
			close_stdin_stdout(&cmd);
		}
	}
	return (0);
}
