/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/23 23:40:15 by nlibano-         ###   ########.fr       */
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
				count_pipe(&cmd, cmd.cmd_line); //cuenta el numero de pipes para hacer los hijos
				cmd.cmd = split(cmd.cmd_line, '|');
				int i = -1;
				while(cmd.cmd[++i])
				{
					cmd.cmd[i] = ft_deletequotes(cmd.cmd[i]);
					if(i > 1)
					{
						if(cmd.cmd[i][0] == ' ')
							cmd.cmd[i] = ft_strtrim(cmd.cmd[i], " "); //para quitar los espacios.
					}
				}
				save_cmds(&cmd); //aqui ya mando los cmd "limpios"
				pipex_main(&cmd); //la funcion de los pipes!!
				if(cmd.num_pipes == 0)
				{
					//la funcion esta en path.c
					ft_execve(cmd.pipe, cmd.env); //En esta funcion miramos lo que hay que ejecutar
											//tanto si es bultin como un cmd normal.
									
				}
 				else
				{
					i = - 1;
					while(++i <= cmd.num_pipes)
					{
					  //aqui la funcion pipe para ejecutar los pipes, tenemos que mirar
					  // el funcionamiento del outfile e infile.
					}
				} 
			}
			//estoy probando si funciona. TODO: hacer que funcione.
		}
		//pdte liberar (t_env) env
	}
	return (0);
}

/*char	*join_str(char **sp, int start, int fin)
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
*/

void	save_cmds(t_cmd *cmd)
{
	int		i;
	char	**sp;
	int		start;
	t_pipe	*pipe;
	char	*infile;
	char	*outfile;
	char	*key;

//el NULL del final esta cogiendo como string en lugar del NULO.
	start = 0;
	sp = ft_split(cmd->cmd_line, '\n');
	i = -1;
	while (sp[++i])
	{
		if (ft_strncmp(sp[i], "|", 1) == 0)
		{
			// crear listas para pipe. crear, añadir, borrar....
			pipe = ft_newpipe();
			pipe->full_cmd = subsplit(sp, start, i - start);
			pipe->path = get_path(sp[start], cmd->env);
			// 1: redireccionar la salida a un pipe
			pipe->outfile = 1;
			ft_pipeadd_back(&(cmd->pipe), pipe);
//			printf("cmd:%s path:%s\n", pipe->full_cmd, pipe->path);
			start = i + 1;
		}
		else if (ft_strcmp(sp[i], "<<"))
			key = ft_strdup(sp[i + 1]);
		else if (ft_strcmp(sp[i], "<"))
			infile = ft_strdup(sp[i + 1]);
		else if (ft_strcmp(sp[i], ">"))
			outfile = ft_strdup(sp[i + 1]);
		else if (ft_strcmp(sp[i], ">>"))
			outfile = ft_strdup(sp[i + 1]);
	}
	if (start < i)
	{
		pipe = ft_newpipe();
		pipe->full_cmd = subsplit(sp, start, i - start);
		pipe->path = get_path(sp[start], cmd->env);
		ft_pipeadd_back(&(cmd->pipe), pipe);
	}
	free_split(sp);
}
