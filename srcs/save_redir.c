/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:15:25 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/24 16:26:03 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

void	save_redir(char *str, char *next, int *flag, t_redir *redir)
{
	save_redir_readline(str, next, flag, redir);
	save_redir_read(str, next, flag, redir);
	save_redir_write(str, next, flag, redir);
	save_redir_append(str, next, flag, redir);
}
