/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/13 21:39:20 by nlibano-         ###   ########.fr       */
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

int	redirections(t_pipe *pipes)
{
	int		i;
	t_redir	*redir;

	if (!pipes->redir)
		return (0);
	redir = pipes->redir;
	i = -1;
	while (++i < pipes->num_redi)
	{
		if(redir[i].fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redir[i].file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (g_shell.quit_status = 1);
		}
		if (redir[i].fd == 0)
			return  (0);
		if (!ft_strcmp(redir[i].type, "read"))
		{
			close(redir[i].fd);
			dup2(redir[i].fd, STDIN_FILENO);
		}
		if (!ft_strcmp(redir[i].type, "write"))
		{
			redir[i].fd = open_file(redir[i].file, 'w');
			dup2(redir[i].fd, STDOUT_FILENO);
		}
		if (!ft_strcmp(redir[i].type, "append"))
		{
			redir[i].fd = open_file(redir[i].file, 'a');
			dup2(redir[i].fd, STDOUT_FILENO);
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
			return (fd);
		}
	}
	return (fd);
}
