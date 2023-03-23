/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:49:16 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/23 23:16:21 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	delete_redir_len(char **s, int *len)
{
	int	i;

	*len = 0;
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
	return (*len);
}

char	**delete_redirection(char *sp, int *len)
{
	int		i;
	int		j;
	char	**res;
	char	**s;

	s = ft_split(sp, '\n');
	res = (char **)malloc(sizeof(char *) * (delete_redir_len(s, len) + 1));
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

int	save_empty(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = ft_newpipe();
	pipe->full_cmd = fill_empty();
	pipe->path = ft_strdup("");
	ft_pipeadd_back(&(cmd->pipe), pipe);
	return (0);
}

int	init_redir_size(t_pipe **pipe)
{
	if ((*pipe)->num_redi > 0)
	{
		(*pipe)->redir = malloc(sizeof(t_redir) * ((*pipe)->num_redi + 1));
		if (!(*pipe)->redir)
			return (1);
	}
	return (0);
}

void	save_redir_readline(char *str, char *next, int *flag, t_redir *redir)
{
	if (!ft_strcmp(str, "<<"))
	{
		*redir = init_redirection(NULL, "readl", ft_deletequotes(next));
		redir->fd = 1;
		*flag = 1;
	}
}

void	save_redir_read(char *str, char *next, int *flag, t_redir *redir)
{
	char	*aux;

	if (!ft_strcmp(str, "<"))
	{
		*redir = init_redirection(ft_deletequotes(next), "read", NULL);
		aux = ft_deletequotes(next);
		redir->fd = open_file(aux, 'r');
		free(aux);
		*flag = 1;
	}
}

void	save_redir_write(char *str, char *next, int *flag, t_redir *redir)
{
	char	*aux;

	if (!ft_strcmp(str, ">"))
	{
		*redir = init_redirection(ft_deletequotes(next), "write", NULL);
		aux = ft_deletequotes(next);
		redir->fd = open_file(aux, 'w');
		free(aux);
		*flag = 1;
	}
}

void	save_redir_append(char *str, char *next, int *flag, t_redir *redir)
{
	char	*aux;

	if (!ft_strcmp(str, ">>"))
	{
		*redir = init_redirection(ft_deletequotes(next), "append", NULL);
		aux = ft_deletequotes(next);
		redir->fd = open_file(aux, 'a');
		free(aux);
		*flag = 1;
	}
}

int	error_pipe_redir(t_pipe *pipe)
{
	char	*tmp;

	if (!pipe->redir && find_str('/', pipe->full_cmd[0]) && \
		!is_builtin(pipe->path) && access(pipe->path, F_OK) != 0)
	{
		tmp = ft_deletequotes(pipe->full_cmd[0]);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		return (g_shell.quit_status = 127);
	}
	return (0);
}

char	**save_cmd_redir(char *s, char **sp, int *j, t_redir **pipe_redir)
{
	int		k;
	int		flag;
	t_redir	redir;

	flag = 0;
	*j = -1;
	k = -1;
	while (sp[++(*j)])
	{
		save_redir_readline(sp[*j], sp[*j + 1], &flag, &redir);
		save_redir_read(sp[*j], sp[*j + 1], &flag, &redir);
		save_redir_write(sp[*j], sp[*j + 1], &flag, &redir);
		save_redir_append(sp[*j], sp[*j + 1], &flag, &redir);
		if (flag == 1)
		{
			k++;
			(*pipe_redir)[k] = redir;
			flag = 0;
		}
	}
	if (k != -1)
	{
		free_split(sp);
		sp = delete_redirection(s, j);
	}
	return (sp);
}

int	save_cmds(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**sp;
	char	**sp2;
	t_pipe	*pipe;

	if (ft_strlen(cmd->cmd_line) == 0)
		return (save_empty(cmd));
	sp = split(cmd->cmd_line, '|');
	i = -1;
	while (sp[++i])
	{
		pipe = ft_newpipe();
		pipe->num_redi = count_redirections(sp[i]);
		if (init_redir_size(&pipe) == 1)
			return (1);
		sp2 = ft_split(sp[i], '\n');
		sp2 = save_cmd_redir(sp[i], sp2, &j, &(pipe->redir));
		pipe->full_cmd = subsplit(sp2, 0, j);
		pipe->path = get_path(sp2[0], cmd->env);
		if (error_pipe_redir(pipe) != 0)
			return (g_shell.quit_status);
		if (!cmd->pipe && !pipe->redir && (!ft_strcmp(pipe->full_cmd[0], "cat") \
			|| !ft_strcmp(pipe->full_cmd[0], "/bin/cat")) && \
			(!pipe->full_cmd[1] || !ft_strcmp(pipe->full_cmd[1], "-e")))
			pipe->wait = 1;
		ft_pipeadd_back(&(cmd->pipe), pipe);
		free_split(sp2);
	}
	free_split(sp);
	return (0);
}
