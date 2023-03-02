/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:22:03 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/03 00:40:12 by nlibano-         ###   ########.fr       */
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

void	cd_no_argumnets(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "HOME"));
	update_val(cmd, "OLDPWD", oldpwd);
	update_val(cmd, "PWD", pwd);
	chdir(pwd);
	free(oldpwd);
	free(pwd);
}

void	cd_up_dir(t_cmd *cmd)
{
	char	*tmp;
	char	*pwd;
	int		i;

	pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	i = ft_strlen(pwd);
	while (pwd[--i])
	{
		if (pwd[i] == '/')
		{
			tmp = ft_substr(pwd, 0, i);
			update_val(cmd, "OLDPWD", pwd);
			update_val(cmd, "PWD", tmp);
			chdir(tmp);
			free(pwd);
			free(tmp);
			return ;
		}
	}
	free(pwd);
}

void	cd_undo(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "OLDPWD"));
	if (ft_strlen(oldpwd) == 0)
	{
		ft_putstr_fd("error: bash: cd: OLDPWD not set\n", 2);
		return ;
	}
	pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	update_val(cmd, "PWD", oldpwd);
	update_val(cmd, "OLDPWD", pwd);
	chdir(oldpwd);
	ft_putstr_fd(oldpwd, 1);
	ft_putstr_fd("\n", 1);
	free(oldpwd);
	free(pwd);
}

void	cd_absolute_path(t_cmd *cmd)
{
	char	*oldpwd;

	if (chdir(cmd->pipe->full_cmd[1]) == 0)
	{
		oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
		update_val(cmd, "PWD", cmd->pipe->full_cmd[1]);
		update_val(cmd, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->pipe->full_cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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

void	cd_relative_path(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	pwd = cd_find_full_path(cmd, oldpwd);
	if (chdir(pwd) == 0)
	{
		free(pwd);
		pwd = getcwd(NULL, 1);
		update_val(cmd, "PWD", pwd);
		update_val(cmd, "OLDPWD", oldpwd);
		free(oldpwd);
		free(pwd);
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->pipe->full_cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(oldpwd);
		free(pwd);
	}
}

void	cd(t_cmd *cmd)
{
	if (ft_strlen(ft_lstfind_env_val(cmd->env, "OLDPWD")) == 0)
		export_add(cmd, "OLDPWD");
	if (!cmd->pipe->full_cmd[1] || !ft_strcmp(cmd->pipe->full_cmd[1], "~"))
		cd_no_argumnets(cmd);
	else if (!ft_strcmp(cmd->pipe->full_cmd[1], ".."))
		cd_up_dir(cmd);
	else if (!ft_strcmp(cmd->pipe->full_cmd[1], "-"))
		cd_undo(cmd);
	else
	{
		if (cmd->pipe->full_cmd[1][0] == '/')
			cd_absolute_path(cmd);
		else
			cd_relative_path(cmd);
	}
	//TODO: cuando sacamos el error hay que expandir ~
}
