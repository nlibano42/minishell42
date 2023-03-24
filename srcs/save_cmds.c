/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:49:16 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/24 16:41:08 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
		save_redir(sp[*j], sp[*j + 1], &flag, &redir);
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
