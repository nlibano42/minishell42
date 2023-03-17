/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/17 00:36:46 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char **argv, char **env)
{	
	t_cmd	cmd;
	int		save_stdin;
	int		save_stdout;

	if (check_init_params(argc, argv))
		return (1);
	g_shell.pid = 0;
	init_cmd(&cmd);
	init_env(&(cmd.env), env);
	ft_signal();
	while (1)
	{
		save_stdin = dup(STDIN_FILENO);
		save_stdout = dup(STDOUT_FILENO);
		cmd.readl = readline("Minishell $> ");
		add_history(cmd.readl);
		if (!cmd.readl)
		{
			//TODO: pone \n antes del exit. Quitar salto de linea inicial
			ft_exit(&cmd);
		}
		if (ft_strlen(cmd.readl) > 0)
		{
			if (check_spaces(cmd.readl) || is_quotes_opened(cmd.readl) \
				|| is_fin_redirection(cmd.readl) || is_open_pipe(cmd.readl) \
					|| line_parse(&cmd, cmd.env))
				continue ;
			else
			{
				count_pipe(&cmd, cmd.cmd_line);
				save_cmds(&cmd);
				pipex_main(&cmd);
				free_all(&cmd);
			}
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
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
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || \
			!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue ;
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
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || \
			!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue ;
		}
		res[j] = ft_strtrim(s[i], " ");
		j++;
	}
	res[j] = NULL;
	free_split(s);
	return (res);
}

char	**fill_empty(void)
{
	char	**s;

	s = (char **)malloc(sizeof(char *) * 2);
	if (!s)
		return (NULL);
	s[0] = ft_strdup("");
	s[1] = NULL;
	return (s);
}

int	count_redirections(char *s)
{
	int		i;
	int		count;
	char	**sp;

	count = 0;
	sp = ft_split(s, '\n');
	i = -1;
	while (sp[++i])
	{
		if (!ft_strcmp(sp[i], "<<") || !ft_strcmp(sp[i], "<") || \
				!ft_strcmp(sp[i], ">") || !ft_strcmp(sp[i], ">>"))
			count++;
	}
	free_split(sp);
	return (count);
}

void	save_cmds(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**sp;
	char	**sp2;
	int		flag;
	t_pipe	*pipe;
	t_redir	redir;
	flag = 0;
	if (ft_strlen(cmd->cmd_line) == 0)
	{
		pipe = ft_newpipe();
		pipe->full_cmd = fill_empty();
		pipe->path = ft_strdup("");
		ft_pipeadd_back(&(cmd->pipe), pipe);
		return ;
	}
	sp = split(cmd->cmd_line, '|');
	i = -1;
	while (sp[++i])
	{
		pipe = ft_newpipe();
		pipe->num_redi = count_redirections(sp[i]);
		if (pipe->num_redi > 0)
		{
			pipe->redir = malloc(sizeof(t_redir) * (pipe->num_redi + 1));
			if (!pipe->redir)
				return ;
		}
		sp2 = ft_split(sp[i], '\n');
		j = -1;
		k = -1;
		while (sp2[++j])
		{
			if (!ft_strcmp(sp2[j], "<<"))
			{
				redir = init_redirection(NULL, "readl", ft_strdup(sp2[j + 1]));
				redir.fd = 1;
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], "<"))
			{
				redir = init_redirection(ft_strdup(sp2[j + 1]), "read", NULL);
				redir.fd = open_file(sp2[j + 1], 'r');
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], ">"))
			{
				redir = init_redirection(ft_strdup(sp2[j + 1]), "write", NULL);
				redir.fd = open_file(sp2[j + 1], 'w');
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], ">>"))
			{
				redir = init_redirection(ft_strdup(sp2[j + 1]), "append", NULL);
				redir.fd = open_file(sp2[j + 1], 'a');
				flag = 1;
			}
			if (flag == 1)
			{
				k++;
				pipe->redir[k] = redir;
				flag = 0;
			}
		}
		if (k != -1)
		{
			free_split(sp2);
			sp2 = delete_redirection(sp[i], &j);
		}
		pipe->full_cmd = subsplit(sp2, 0, j);
		pipe->path = get_path(sp2[0], cmd->env);
		ft_pipeadd_back(&(cmd->pipe), pipe);
	}
	free_split(sp);
	free_split(sp2);
	// TODO. cerrar los descriptores cuando no se necesiten y en otro punto.
}
