/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:04:10 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/01 01:50:33 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*void echo (t_cmd *cmd)
{
	char	**line;
	int		i;
	int		j;
	int		flag;
	// esta casi cuando escribes -n -nn -nl hola el output tiene q ser -nl hola.
	line = cmd->pipe->full_cmd;
	flag = 1;
	i = -1;
//	while(line[++i])
//		printf("cmd:%s\n", line[i]);
	i = 0;
	while(line[++i] && flag == 1)
	{
		if(!ft_strcmp(ft_deletequotes(line[i]), "-n"))
//		{
//			flag = 1;
			continue ;
//		}
		else if(line[i][1] == ' ')
			break;
		else if(line[i][0] == '-')
		{
			j = 0;
			while(line[i][++j])
			{
				if(line[i][j] == 'n')
//				{
//					flag = 1;
					continue;
//				}
				else
				{
					flag = 0;
					break;
				}
			}
		}
	}
	while (line[i])
	{
		ft_putstr_fd(ft_deletequotes(line[i]), 1);
		i++;
	}
	if(flag == 0)
	{
		i --;
		while(line[i])
		{
			ft_putstr_fd(ft_deletequotes(line[i]), 1);
			if(line[i + 1])
				ft_putstr_fd(" ", 1);
			i ++;
		}
	}
	else
	{
		i = 0;
		while(line[++i])
		{
			ft_putstr_fd(ft_deletequotes(line[i]), 1);
			if(line[i + 1])
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	
}*/

/*void echo (t_cmd *cmd)
{
	char	**line;
	int		i;
	int		j;
	int		flag;
	int		nl;
	int		start;
	
	flag = 0;
	nl = 0;
	start = 0;
	line = cmd->pipe->full_cmd;
	i = 0;
	while (line[++i] && flag == 0)
	{
//		while (!ft_strcmp(line[i], "-n"))
//			i++;
		if (line[i][0] == '-')
		{
			j = 0;
			while (line[i][++j])
			{
				if (line[i][j] == 'n')
					continue ;
				else
				{
					start = i - 1;
					flag = 1;
				}
			}
			if (flag == 0)
				nl = 1;
		}
		else
			flag = 1;
		start = i - 1;
		//	i++;
	}
//	i = start;
i--;
	while (line[++i])
	{
		if (i != start + 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(ft_deletequotes(line[i]), 1);
	}
	if (nl == 0)
		ft_putchar_fd('\n', 1);
}*/

void	print_echo(char **s, int n)
{
	int		i;
	char	*str;

	i = -1;
	while (s[++i])
	{
		if (i != 0)
			ft_putchar_fd(' ', 1);
		str = ft_deletequotes(s[i]);
		ft_putstr_fd(str, 1);
		free(str);
	}
	if (n == 1)
		ft_putchar_fd('\n', 1);
}

int	echo_find_n_option(char **str, char *s, int i)
{
	int	j;

	j = 0;
	while (s[++j])
	{
		if (s[j] != 'n')
		{
			print_echo(&str[i], i);
			free(s);
			return (1);
		}
	}
	return (0);
}

void	echo(t_cmd *cmd)
{
	char	*s;
	int		i;

	i = 0;
	while (cmd->pipe->full_cmd[++i])
	{
		s = ft_deletequotes(cmd->pipe->full_cmd[i]);
		if (s[0] == '-')
		{
			if (echo_find_n_option(cmd->pipe->full_cmd, s, i))
				return ;
		}
		else
		{
			print_echo(&cmd->pipe->full_cmd[i], i);
			free(s);
			return ;
		}
		free(s);
	}
	if (i == 1)
		ft_putchar_fd('\n', 1);
}
