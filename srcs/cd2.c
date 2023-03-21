/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:44:07 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/21 14:48:07 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	update_val(t_cmd *cmd, char *name, char *val)
{
	t_env	*env;

	env = cmd->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->val);
			env->val = ft_strdup(val);
			break ;
		}
		env = env->next;
	}
}

char	*cd_find_full_path(t_cmd *cmd, char *oldpwd)
{
	char	*home;
	char	*pwd;

	if (cmd->pipe->full_cmd[1][0] == '~')
	{
		home = ft_strdup(ft_lstfind_env_val(cmd->env, "HOME"));
		pwd = ft_strjoin(home, ft_substr(cmd->pipe->full_cmd[1], 1, \
			ft_strlen(cmd->pipe->full_cmd[1])));
	}
	else
	{
		pwd = ft_strjoin(ft_strdup(oldpwd), ft_strdup("/"));
		pwd = ft_strjoin(pwd, ft_strdup(cmd->pipe->full_cmd[1]));
	}
	return (pwd);
}

void	cd_relative_path(t_cmd *cmd, t_pipe *pipex)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;

	oldpwd = ft_lstfind_env_val(cmd->env, "PWD");
	pwd = cd_find_full_path(cmd, oldpwd);
	if (chdir(pwd) == 0)
	{
		free(pwd);
		pwd = getcwd(NULL, 1);
		if (pwd[ft_strlen(pwd) - 1] == '/')
		{
			tmp = ft_substr(pwd, 0, ft_strlen(pwd) - 1);
			update_val(cmd, "PWD", tmp);
			free(tmp);
		}
		else
			update_val(cmd, "PWD", pwd);
		update_val(cmd, "OLDPWD", oldpwd);
	}
	else
		error_cd_relative_path(pipex->full_cmd[1]);
	free(pwd);
}

void	cd_absolute_path(t_cmd *cmd, t_pipe *pipex)
{
	char	*oldpwd;
	char	*tmp;
	char	*pwd;

	pwd = pipex->full_cmd[1];
	if (chdir(pwd) == 0)
	{
		oldpwd = ft_lstfind_env_val(cmd->env, "PWD");
		if (pwd[ft_strlen(pwd) - 1] == '/')
		{
			tmp = ft_substr(pwd, 0, ft_strlen(pwd) - 1);
			update_val(cmd, "PWD", tmp);
			free(tmp);
		}
		else
			update_val(cmd, "PWD", pwd);
		update_val(cmd, "OLDPWD", oldpwd);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(pipex->full_cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	cd_dot_get_path(char *pwd, char **tmp, int i)
{
	if (pwd[i] == '/')
	{
		if (i == 0)
			*tmp = ft_strdup("/");
		else
			*tmp = ft_substr(pwd, 0, i);
		return (1);
	}
	return (0);
}
