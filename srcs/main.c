/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/07 21:12:44 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->readl = NULL;
}

void	ft_signal()
{	
	ft_suppress_output();
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);	
}

int	main(int argc, char **argv, char **env)
{	
	t_cmd	*cmd;
	t_env	*envp = NULL;

	(void)argc;
	(void)argv;
	init_env(&(envp), env);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if(!cmd)
		return (-1);
	init_cmd(cmd);
	ft_signal();
	while (1)
	{
		cmd->readl = readline("Minishell $> ");
		add_history(cmd->readl);
		if (!cmd->readl)
		{
			printf("exit\n");
			//usar nuestro builtin de exit en lugar de exit()
			exit(g_shell.quit_status);
		}
		if (ft_strlen(cmd->readl) > 0)
		{
			if(linecontrol(cmd->readl, envp))
			{
				
			}
		}
		//pdte liberar (t_env) env
	}
	return (0);
}