/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/22 20:41:01 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	open_file(char *file, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'r')
		fd = open(file, O_RDONLY);
	else if (flag == 'w')
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'a')
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		g_shell.quit_status = 1;
	return (fd);
}

int	last_redirec(t_redir *redir, int i, int len)
{
	while (++i < len)
	{
		if (!ft_strcmp(redir[i].type, "readl"))
			return (1);
	}
	return (0);
}

int	redirections(t_pipe *pipes)
{
	int		i;

	if (!pipes->redir)
		return (0);
	i = -1;
	while (++i < pipes->num_redi)
	{
		if (pipes->redir[i].fd == -1)
			return (error_open_file(pipes->redir[i].file));
		if (pipes->redir[i].fd == 0)
			return (0);
		action_read(pipes->redir[i].type, pipes->redir[i].fd);
		action_write(pipes->redir[i].type, pipes->redir[i].fd);
		action_append(pipes->redir[i].type, pipes->redir[i].fd);
		action_read_line(pipes, i);
	}
	return (0);
}

int	ft_access(char *input)
{
	int		i;
	char	**cmd_sp;
	int		fd;

	cmd_sp = ft_split(input, '\n');
	fd = 0;
	i = -1;
	while (cmd_sp[++i])
	{
		if (!ft_strncmp(cmd_sp[i], ">", 1) && !access(cmd_sp[i + 1], F_OK))
			fd = access(cmd_sp[i + 1], W_OK);
		if (!ft_strncmp(cmd_sp[i], "<", 1) && !access(cmd_sp[i + 1], F_OK))
			fd = access(cmd_sp[i + 1], R_OK);
		if (!ft_strncmp(cmd_sp[i], ">>", 2) && !access(cmd_sp[i + 1], F_OK))
			fd = access(cmd_sp[i + 1], W_OK);
		if (fd == -1)
		{
			access_error(cmd_sp[i + 1]);
			free_split(cmd_sp);
			return (fd);
		}
	}
	free_split(cmd_sp);
	return (fd);
}
