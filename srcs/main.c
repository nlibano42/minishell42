/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/20 21:20:47 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;
	t_env	*envp = NULL;

	(void)argc;
	(void)argv;
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
			if (is_quotes_opened(cmd.readl) || is_two_pipes(cmd.readl)\
				|| is_open_pipe(cmd.readl) || line_parse(&cmd, envp))
				continue ;
			else
			{
				count_pipe(&cmd, cmd.cmd_line); //cuenta el numero de pipes para hacer los hijos
				cmd.cmd = split(cmd.cmd_line, '|');
				int i = -1;
				while(cmd.cmd[++i])
				{
					cmd.cmd[i] = ft_deletequotes(cmd.cmd[i]);
					
					//printf("%s\n", cmd.cmd[i]);
				}
				if(cmd.num_pipes == 0)
				{
					get_path(cmd.cmd[0], envp);
				}
				else
				{
					i = - 1;
					while(++i <= cmd.num_pipes)
					{
						if(cmd.cmd[i][0] == ' ')
							cmd.cmd[i] = ft_strtrim(cmd.cmd[i], " "); //para quitar los espacios.
						printf("%s\n", cmd.cmd[i]);
					}
				}
				//printf("pipe:%d\n", cmd.num_pipes);
			}
			//estoy probando si funciona. TODO: hacer que funcione.
			
			//esta ando errores
			//redirections(cmd->cmd_line); 
// Esto debe ir en otra parte, donde necesitemos:
		}
		//pdte liberar (t_env) env
	}
	return (0);
}
