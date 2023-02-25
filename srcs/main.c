/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/25 23:09:59 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;

	if (check_init_params(argc, argv))
		return (1);
	g_shell.pid = 0;
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

void	save_cmds(t_cmd *cmd)
{
	int		i;
	char	**sp;
	int		start;
	t_pipe	*pipe;
	t_redir	*redir;

	cmd->pipe = NULL;
	cmd->redir = NULL;
	start = 0;
	sp = ft_split(cmd->cmd_line, '\n');
	i = -1;
	while (sp[++i])
	{
		if (!ft_strncmp(sp[i], "|", 1))
		{
			// crear listas para pipe. crear, añadir, borrar....
			pipe = ft_newpipe();
			pipe->full_cmd = subsplit(sp, start, i - start);
			pipe->path = get_path(sp[start], cmd->env);
			// 1: redireccionar la salida a un pipe
			pipe->outfile = 1;
			ft_pipeadd_back(&(cmd->pipe), pipe);
			//printf("cmd:%s path:%s\n", pipe->full_cmd[0], pipe->path);
			start = i + 1;
		}
		else if (!ft_strcmp(sp[i], "<<"))
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
		}
		else if (!ft_strcmp(sp[i], ">"))
		{
			redir = ft_lstnew_redir();
			redir->file = ft_strdup(sp[i + 1]);
			redir->type = "write";
		}
		else if (!ft_strcmp(sp[i], ">>"))
		{
			redir = ft_lstnew_redir();
			redir->file = ft_strdup(sp[i + 1]);
			redir->type = "append";
		}
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
