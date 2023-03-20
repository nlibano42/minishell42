/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:49:16 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/20 21:27:38 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

int	save_without_redir(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = ft_newpipe();
	pipe->full_cmd = fill_empty();
	pipe->path = ft_strdup("");
	ft_pipeadd_back(&(cmd->pipe), pipe);
	return (0);
}

/*int	save_redirections(char **sp, int i, t_redir	*redir)
{
	int	flag;

	flag == 0
	if (!ft_strcmp(sp[i], "<<"))
	{
		*redir = init_redirection(NULL, "readl", ft_strdup(sp[i + 1]));
		redir->fd = 1;
		flag = 1;
	}
	else if (!ft_strcmp(sp[i], "<"))
	{
		*redir = init_redirection(ft_strdup(sp[i + 1]), "read", NULL);
		redir->fd = open_file(sp[i + 1], 'r');
		flag = 1;
	}
	else if (!ft_strcmp(sp[i], ">"))
	{
		*redir = init_redirection(ft_strdup(sp[i + 1]), "write", NULL);
		redir->fd = open_file(sp[i + 1], 'w');
		flag = 1;
	}
	else if (!ft_strcmp(sp[i], ">>"))
	{
		*redir = init_redirection(ft_strdup(sp[i + 1]), "append", NULL);
		redir->fd = open_file(sp[i + 1], 'a');
		flag = 1;
	}
	return (flag);
}
*/

int	save_cmds(t_cmd *cmd)
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
		return(save_without_redir(cmd));
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
				return (1);
		}
		sp2 = ft_split(sp[i], '\n');
		j = -1;
		k = -1;
		while (sp2[++j])
		{
	//		redir = save_redirections(sp2, j, &flag);
			if (!ft_strcmp(sp2[j], "<<"))
			{
				redir = init_redirection(NULL, "readl", ft_deletequotes(sp2[j + 1]));
				redir.fd = 1;
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], "<"))
			{
				printf("--1--->%s\n", sp2[j + 1]);
				redir = init_redirection(ft_deletequotes(sp2[j + 1]), "read", NULL);
				redir.fd = open_file(sp2[j + 1], 'r');
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], ">"))
			{
				printf("--2--->%s\n", sp2[j + 1]);
				redir = init_redirection(ft_deletequotes(sp2[j + 1]), "write", NULL);
				printf("--2-1-->%s\n",ft_deletequotes(sp2[j + 1]));
				redir.fd = open_file(ft_deletequotes(sp2[j + 1]), 'w');
				flag = 1;
			}
			else if (!ft_strcmp(sp2[j], ">>"))
			{
				//TODO. crear una variable para hacer open y despues liberar
				printf("--3--->%s\n", sp2[j + 1]);
				redir = init_redirection(ft_deletequotes(sp2[j + 1]), "append", NULL);
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
		//	if (!sp2)
				
		}
		pipe->full_cmd = subsplit(sp2, 0, j);
		pipe->path = get_path(sp2[0], cmd->env);
		if (!pipe->redir && find_str('/', pipe->full_cmd[0]) && !is_builtin(pipe->path) && access(pipe->path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(pipe->full_cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (g_shell.quit_status = 127);
		}
		ft_pipeadd_back(&(cmd->pipe), pipe);
		free_split(sp2);
	}
	free_split(sp);
	// TODO. cerrar los descriptores cuando no se necesiten y en otro punto.
	return (0);
}