/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/09 23:00:38 by nlibano-         ###   ########.fr       */
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
		cmd.readl = readline("Minishell $> ");
		add_history(cmd.readl);
		if (!cmd.readl)
		{
			//TODO: pone \n antes del exit. Quitar salto de linea inicial
			ft_exit(&cmd);
//			printf("exit\n");
			//usar nuestro builtin de exit en lugar de exit()
//			exit(g_shell.quit_status);
		}
		//EXIT debe ir en el buitin
		//if(!ft_strncmp(cmd->readl, "exit", 4))
		//	break ;
		if (ft_strlen(cmd.readl) > 0)
		{
			if (check_spaces(cmd.readl) || is_quotes_opened(cmd.readl)\
				|| is_fin_redirection(cmd.readl) || is_open_pipe(cmd.readl)\
					|| line_parse(&cmd, cmd.env))
				continue ;
			else
			{
				count_pipe(&cmd, cmd.cmd_line); //cuenta el numero de pipes para hacer los hijos
				save_cmds(&cmd);
				pipex_main(&cmd); //la funcion de los pipes!!
				free_all(&cmd);
			}
			//estoy probando si funciona. TODO: hacer que funcione.
		}
		//pdte liberar (t_env) env
	}
	return (0);
}

char	**delete_redirection(char *sp, int *len)
{
	int		i;
	int		j;
	char	**res;
	char	**s;

	*len = 0;
	s = ft_split(sp, '\n');
	i = -1;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || !ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue;
		}
		(*len)++;
	}
	res = (char **)malloc(sizeof(char *) * (*len + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || !ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue;
		}
		res[j] = ft_strdup(ft_strtrim(s[i], " "));
		j++;
	}
	res[j] = NULL;
	free_split(s);
	return (res);
}

void	save_cmds(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**sp;
	char	**sp2;
	int		start;
	int		flag;
	t_pipe	*pipe;
	t_redir	*redir;

	start = 0;
	flag = 0;
//	sp = ft_split(cmd->cmd_line, '\n');
	sp = split(cmd->cmd_line, '|');
	i = -1;
	while (sp[++i])
	{
		sp2 = ft_split(sp[i], '\n');
		j = -1;
		while (sp2[++j])
		{
			if (!ft_strcmp(sp2[j], "<<"))
			{
				redir = ft_lstnew_redir();
				redir->key = ft_strdup(sp2[j + 1]);
				redir->type = "readl";
				ft_lstadd_back_redir(&(cmd->redir), redir);
				flag = 1;
				break ;
			}
			else if (!ft_strcmp(sp2[j], "<"))
			{
				redir = ft_lstnew_redir();
				redir->file = ft_strdup(sp2[j + 1]);
				redir->type = "read";
				ft_lstadd_back_redir(&(cmd->redir), redir);
				flag = 1;
				break ;
			}
			else if (!ft_strcmp(sp2[j], ">"))
			{
				redir = ft_lstnew_redir();
				redir->file = ft_strdup(sp2[j + 1]);
				redir->type = "write";
				ft_lstadd_back_redir(&(cmd->redir), redir);
				flag = 1;
				break ;
			}
			else if (!ft_strcmp(sp2[j], ">>"))
			{
				redir = ft_lstnew_redir();
				redir->file = ft_strdup(sp2[j + 1]);
				redir->type = "append";
				ft_lstadd_back_redir(&(cmd->redir), redir);
				flag = 1;
				break ;
			}
		}
		pipe = ft_newpipe();
		if (flag == 1)
		{
			free_split(sp2);
			sp2 = delete_redirection(sp[i], &j);
			// conseguir toda la info quitando la redireccion
		}
		pipe->full_cmd = subsplit(sp2, 0, j);
		pipe->path = get_path(sp2[0], cmd->env);
		//TODO: ver que numero asignar a cada accion. 0 = x defecto, ...
		if (redir)
		{
			pipe->redir = redir;
			if (!ft_strcmp(redir->type, "readl"))
				pipe->infile = 2; //leer desde el terminal
			else if (!ft_strcmp(redir->type, "read"))
				pipe->infile = 1; // leer de un fichero
			else if (!ft_strcmp(redir->type, "write"))
				pipe->outfile = 3; //escribir en el fichero
			else if (!ft_strcmp(redir->type, "apend"))
				pipe->outfile = 4; //escribir en el fichero añadiendo.
		}
		ft_pipeadd_back(&(cmd->pipe), pipe);

//		if (!ft_strcmp(sp[i], "|"))
//		{
/*			// crear listas para pipe. crear, añadir, borrar....
			pipe = ft_newpipe();
			pipe->full_cmd = subsplit(sp, start, i - start);
			pipe->path = get_path(sp[start], cmd->env);
			// 1: redireccionar la salida a un pipe
			pipe->outfile = 1;
			ft_pipeadd_back(&(cmd->pipe), pipe);
			start = i + 1;
*/
//		}
/*		else if (!ft_strcmp(sp[i], "<<"))
		{
			redir = ft_lstnew_redir();
			redir->key = ft_strdup(sp[i + 1]);
			redir->type = "readl";
			ft_lstadd_back_redir(&(cmd->redir), redir);
		}
		else if (!ft_strcmp(sp[i], "<"))
		{
			redir = ft_lstnew_redir();
			redir->file = ft_strdup(sp[i + 1]);
			redir->type = "read";
			ft_lstadd_back_redir(&(cmd->redir), redir);
		}
		else if (!ft_strcmp(sp[i], ">"))
		{
			redir = ft_lstnew_redir();
			redir->file = ft_strdup(sp[i + 1]);
			redir->type = "write";
			ft_lstadd_back_redir(&(cmd->redir), redir);
	}
		else if (!ft_strcmp(sp[i], ">>"))
		{
			redir = ft_lstnew_redir();
			redir->file = ft_strdup(sp[i + 1]);
			redir->type = "append";
			ft_lstadd_back_redir(&(cmd->redir), redir);
		}
*/
	}
/*	if (start < i)
	{
		pipe = ft_newpipe();
		pipe->full_cmd = subsplit(sp, start, i - start);
		pipe->path = get_path(sp[start], cmd->env);
		ft_pipeadd_back(&(cmd->pipe), pipe);
	}
*/
	free_split(sp);
	free_split(sp2);
}
