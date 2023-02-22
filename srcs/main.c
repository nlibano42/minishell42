/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/22 01:12:01 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;
//	t_env	*envp = NULL;

	(void)argc;
	(void)argv;
	cmd.env = NULL;
	init_env(&(cmd.env), env);
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
			if (is_quotes_opened(cmd.readl) || is_fin_redirection(cmd.readl)\
				 || is_open_pipe(cmd.readl) || line_parse(&cmd, cmd.env))
				continue ;
			else
			{
				save_cmds(&cmd);
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
					get_path(cmd.cmd[0], cmd.env);
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

char	*join_str(char **sp, int start, int fin)
{
	int		i;
	char	*s;

	s = ft_strdup("");
	i = start - 1;
	while (++i <= fin)
	{
		s = ft_strjoin(s, ft_strtrim(sp[i], " "));
		if (i != fin)
			s = ft_strjoin(s, ft_strdup(" "));
	}
	return (s);
}

int	save_cmds(t_cmd *cmd)
{
	int		i;
	char	**sp;
	int		start;
	t_pipe	*pipe;

	start = 0;
	sp = ft_split(cmd->cmd_line, '\n');
	i = -1;
	while (sp[++i])
	{
		if (ft_strncmp(sp[i], "|", 1) == 0)
		{
			// crear listas para pipe. crear, añadir, borrar....
			pipe = ft_newpipe();
			pipe->full_cmd = join_str(sp, start, i - 1);
			pipe->path = get_path(sp[start], cmd->env);
			pipe->outfile = 1;
			start = i + 1;
		}
	}
	free_split(sp);
	return (0);
}

char	*get_path(char *s, t_env *env)
{
	char	*path;
	char	**sp;
	int		i;

	if (!ft_strcmp(s, "echo")|| !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd") || \
	!ft_strcmp(s, "export") || !ft_strcmp(s, "unset") || \
	!ft_strcmp(s, "env") || !ft_strcmp(s, "exit"))
		return (s);
	else
	{
		path = ft_lstfind_env_val(env, "PATH");
		sp = ft_split(path, ':');
		i = -1;
		while(sp[++i])
		{
			path = ft_strjoin(ft_strdup(sp[i]), ft_strdup("/"));
			path = ft_strjoin(path, ft_strdup(s));
	 		if(access(sp[i], F_OK) == 0)
			{
				free_split(sp);
				return (path);
			}
		}
		free_split(sp);
	}
	return (NULL);
}