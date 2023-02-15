/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/15 20:09:33 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->readl = NULL;
}

void	ft_signal(void)
{	
	ft_suppress_output();
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;
	t_env	*envp;

	(void)argc;
	(void)argv;
	envp = NULL;
	init_env(&(envp), env);
	init_cmd(&cmd);
	ft_signal();
	while (1)
	{
		cmd.readl = readline("Minishell $> ");
		add_history(cmd.readl);
		if (!cmd.readl)
		{
			printf("exit\n");
			//usar nuestro builtin de exit en lugar de exit()
			exit(g_shell.quit_status);
		}
		//EXIT debe ir en el buitin
		//if(!ft_strncmp(cmd->readl, "exit", 4))
		//	break ;
		if (ft_strlen(cmd.readl) > 0)
		{
			linecontrol(&cmd, envp);
			//esta ando errores
			//redirections(cmd->cmd_line); 
// Esto debe ir en otra parte, donde necesitemos:
//			cmd->cmd_line = ft_deletequotes(cmd->cmd_line);
		}
		//pdte liberar (t_env) env
	}
	return (0);
}