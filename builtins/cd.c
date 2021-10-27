/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/26 15:40:29 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*cd_dash(t_env *env, int fd)
{
	if (srch_and_return_env_var(env, "OLDPWD")
		&& (srch_and_return_env_var(env, "OLDPWD")->value
			&& srch_and_return_env_var(env, "OLDPWD")->value[0] != '\0'))
	{
		ft_putstr_fd(srch_and_return_env_var(env, "OLDPWD")->value, fd);
		ft_putstr_fd("\n", fd);
		return (srch_and_return_env_var(env, "OLDPWD")->value);
	}
	else
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	return (NULL);
}

char	*choose_path(const char *path, t_env *env, int fd)
{
	t_env	*home_env;

	if (!path)
	{
		home_env = srch_and_return_env_var(env, "HOME");
		if (home_env == NULL)
		{
			printf("minishell: cd: Home not set\n");
			return (NULL);
		}
		else
			return (home_env->value);
	}
	else
	{
		if (ft_strcmp(path, "-") == 0)
			return (cd_dash(env, fd));
		else
			return ((char *)path);
	}
}

char	*set_oldpwd(t_shell *shell)
{
	char	old_path[PATH_MAX];
	char	*dup_old_path;
	t_env	*env_pwd;

	env_pwd = srch_and_return_env_var(shell->env, "PWD");
	if (env_pwd == NULL)
	{
		if (shell->cmd.set_old_to_null == 1)
		{
			shell->cmd.set_old_to_null = 0;
			return (ft_strdup("\0"));
		}
		getcwd(old_path, PATH_MAX);
		dup_old_path = ft_strdup(old_path);
	}
	else
		dup_old_path = ft_strdup(env_pwd->value);
	return (dup_old_path);
}

int	cd_exec(char *path, t_shell *shell, t_pars **cmd_parsed)
{
	char	new_path[PATH_MAX];
	char	*dup_old_path;
	char	*dup_path;

	if (chdir(choose_path(path, shell->env, shell->cmd.fd_out)) == 0)
	{
		dup_old_path = set_oldpwd(shell);
		if (srch_and_rplce_env_var(shell->env, "OLDPWD", dup_old_path, 0) == 0)
			ft_lstadd_back_env(&shell->env, ft_lstnew_env(ft_strdup("OLDPWD"), \
				dup_old_path));
		getcwd(new_path, PATH_MAX);
		dup_path = ft_strdup(new_path);
		if (srch_and_rplce_env_var(shell->env, "PWD", dup_path, 0) == 0)
			free(dup_path);
		shell->cmd.exit_status = 0;
		(*cmd_parsed) = (*cmd_parsed)->next;
		return (0);
	}
	if (errno != 14)
		print_error(errno);
	shell->cmd.exit_status = 1;
	(*cmd_parsed) = (*cmd_parsed)->next;
	return (1);
}

int	ft_cd(t_shell *shell, t_pars **cmd_parsed)
{
	char	*path;

	errno = 0;
	path = NULL;
	if ((*cmd_parsed)->next)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		path = (*cmd_parsed)->value;
	}
	if ((*cmd_parsed)->type == 1 || (*cmd_parsed)->type == 2
		|| (*cmd_parsed)->type == 5)
		return (cd_exec(path, shell, cmd_parsed));
	return (0);
}
