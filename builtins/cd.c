/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/20 12:44:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*choose_path(const char *path, t_env *env)
{
	t_env	*home_env;
	
	if (!path)
	{
		home_env = srch_and_return_env_var(env, "HOME");
		if (home_env == NULL)
		{
			printf("Home is not set\n");
			return (NULL); //Call error function instead
		}
		else
			return (home_env->value);
	}
	else
	{
		if (ft_strcmp(path, "-") == 0)
			return (srch_and_return_env_var(env, "OLDPWD")->value);
		else
			return ((char *)path);
	}
}

char	*set_oldpwd(t_shell *shell)
{
	char	old_path[PATH_MAX];
	char	*dup_old_path;
	t_env	*env_pwd;

	env_pwd = srch_and_return_env_var(shell->env, "PWD");// A faire : Mettre OLDPWD a \0 au premier cd quand PWD est supprimer 
	if (env_pwd == NULL)
	{
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

	dup_old_path = set_oldpwd(shell);
	if (chdir(choose_path(path, shell->env)) == 0)
	{
		dup_old_path = set_oldpwd(shell);
		srch_and_rplce_env_var(shell->env, "OLDPWD", dup_old_path, 0);
		getcwd(new_path, PATH_MAX);
		dup_path = ft_strdup(new_path); // Obligé de Dup pour pouvoir free plus tard dans la prochaine fonction
		srch_and_rplce_env_var(shell->env, "PWD", dup_path, 0);
		shell->cmd.exit_status = 0;
		(*cmd_parsed) = (*cmd_parsed)->next;
		return (0);
	}
	else
	{
		print_error(errno);
		shell->cmd.exit_status = 1;
		(*cmd_parsed) = (*cmd_parsed)->next;
		return (1);
	}
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
		|| (*cmd_parsed)->type == 5) // si le type et une commande ou un argument
		return (cd_exec(path, shell, cmd_parsed));
	return (0);
}