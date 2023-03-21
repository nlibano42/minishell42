/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:24:18 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/21 17:59:41 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_syntax_error(char *s, int *i)
{
	int j;
	
	j = *i;
	while(s[j])
	{
		if(find_str(s[j], "*&/|()"))
		{
			ft_putstr_fd("Minishell: syntax error\n", 2);
			free(s);
			return (1);
		}
		j++;
	}
	return (0);
} 

int	check_error_unexpected_token(char *s, int *i)
{
	int j;
	
	j = *i + 1;
	while(s[j])
	{
		printf("%c\n", s[j]);
		if(s[j] != ' ')
			break ;
		if (s[j] == '>' || s[j] == '<')
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			free(s);
		return (1);
		}
		j++;
	}
	return (0);
}

int	check_redirection(char *s, int *i)
{
	if(s[*i] == '>' && s[*i + 1] == '<')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
		free(s);
		return (1);
	}
	if (s[*i + 1] == '<' || s[*i + 1] == '>')
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		free(s);
		return (1);
	}
	return (0);
}

int check_unexpected_newline(char *s, int *i)
{
	if(s[*i + 1] == '\0')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token 'newline'\n", 2);
		free(s);
		return (1);
	}
	return (0);
}