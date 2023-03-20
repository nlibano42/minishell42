/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:22:03 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/20 14:13:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	cd_no_argumnets(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;

	home = ft_lstfind_env_val(cmd->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (g_shell.quit_status = 1);
	}
	oldpwd = ft_lstfind_env_val(cmd->env, "OLDPWD");
	if (!oldpwd)
		export_add(cmd, "OLDPWD");
	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	pwd = ft_strdup(home);
	update_val(cmd, "OLDPWD", oldpwd);
	update_val(cmd, "PWD", pwd);
	chdir(pwd);
	free(oldpwd);
	free(pwd);
	return (g_shell.quit_status = 0);
}

void	cd_up_dir(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;
	int		i;

//pwd -> oldpwd
//pwd -> new (up) -> si pwd no existe, getpwd y subir una -> oldpwd = "", pwd = crearlo con el nuevo valor

	pwd = ft_lstfind_env_val(cmd->env, "PWD");
	if (!pwd)
	{
		pwd = (char *)malloc(sizeof(char) * PATH_MAX);
		getcwd(pwd, PATH_MAX);
		export_add(cmd, "PWD");
		oldpwd = "";
	}
	else
	{
		pwd = ft_strdup(pwd);
		oldpwd = pwd;
	}
	tmp = ft_strdup(pwd);
	i = ft_strlen(pwd);
	while (pwd[--i])
	{
		if (pwd[i] == '/')
		{
			tmp = ft_substr(pwd, 0, i);
			break ;
		}
	}
	update_val(cmd, "OLDPWD", oldpwd);
	update_val(cmd, "PWD", tmp);
	chdir(tmp);
	free(pwd);
	free(tmp);
	return ;
}

int	cd_undo(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	if (!ft_lstfind_env_val(cmd->env, "OLDPWD"))
	{
		ft_putstr_fd("error: bash: cd: OLDPWD not set\n", 2);
		return (g_shell.quit_status = 1);
	}
	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "OLDPWD"));
	if (ft_strlen(oldpwd) == 0)
	{
		ft_putstr_fd("error: bash: cd: OLDPWD not set\n", 2);
		free(oldpwd);
		return (g_shell.quit_status = 1);
	}
	pwd = ft_lstfind_env_val(cmd->env, "PWD");
	if (pwd)
		update_val(cmd, "OLDPWD", pwd);
	update_val(cmd, "PWD", oldpwd);
	chdir(oldpwd);
	ft_putstr_fd(oldpwd, 1);
	ft_putstr_fd("\n", 1);
	free(oldpwd);
	return (0);
}

void	cd(t_cmd *cmd, t_pipe *pipex)
{
	if (!pipex->full_cmd[1] || !ft_strcmp(pipex->full_cmd[1], "~"))
		cd_no_argumnets(cmd);
	else if (!ft_strcmp(pipex->full_cmd[1], ".."))
		cd_up_dir(cmd);
	else if (!ft_strcmp(pipex->full_cmd[1], "-"))
		cd_undo(cmd);
	else
	{
		if (pipex->full_cmd[1][0] == '/')
			cd_absolute_path(cmd, pipex);
		else
			cd_relative_path(cmd, pipex);
	}
	//TODO: cuando sacamos el error hay que expandir ~
}
