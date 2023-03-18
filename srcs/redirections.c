/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/18 16:42:00 by jdasilva         ###   ########.fr       */
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
		g_shell.quit_status = 1; //mirar que numero debe devolver.
	return (fd);
}

int	last_redirec(t_redir *redir, int i, int len)
{
	while(++i < len)
	{
		if(!ft_strcmp(redir[i].type, "readl"))
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
		if(pipes->redir[i].fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(pipes->redir[i].file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (g_shell.quit_status = 1);
		}
		if (pipes->redir[i].fd == 0)
			return  (0);
		if (!ft_strcmp(pipes->redir[i].type, "read"))
		{
			dup2(pipes->redir[i].fd, STDIN_FILENO);
			close(pipes->redir[i].fd);
		}
		if (!ft_strcmp(pipes->redir[i].type, "write"))
		{
			dup2(pipes->redir[i].fd, STDOUT_FILENO);
			close(pipes->redir[i].fd);
		}
		if (!ft_strcmp(pipes->redir[i].type, "append"))
		{
			dup2(pipes->redir[i].fd, STDOUT_FILENO);
			close(pipes->redir[i].fd);
		}
		if (!ft_strcmp(pipes->redir[i].type, "readl")) //TODO: <<< o mas ERROR. igual al reves.
		//TODO vigiliar que "ls | > " fichero o "ls | >> " de error.
		{
			dup2(pipes->redir[i].fd, STDIN_FILENO);
			if (last_redirec(pipes->redir, i, pipes->num_redi) == 1)
				write_pipe_not_last(pipes->fd, pipes, i);
			else
				ft_here_doc(pipes, i);
		}
	}
	return (0);
}

int	ft_access(char *input)
{
	int		i;
	char	**cmd_split;
	int		fd;

	cmd_split = ft_split(input, '\n');
	fd = 0;
	i = -1;
	while (cmd_split[++i])
	{
		if (!ft_strncmp(cmd_split[i], ">", 1) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], W_OK);
		if (!ft_strncmp(cmd_split[i], "<", 1) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], R_OK );
		if (!ft_strncmp(cmd_split[i], ">>", 2) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], W_OK);
		if (fd == -1)
		{
			access_error(cmd_split[i + 1]);
			free_split(cmd_split);
			return (fd);
		}
	}
	free_split(cmd_split);
	return (fd);
}
