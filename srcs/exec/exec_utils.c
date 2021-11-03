/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 08:30:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 09:05:10 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_exec_path(char *path_dir, struct dirent *pdirent, char **path)
{
	char	*temp;

	*path = path_dir;
	temp = ft_strjoin(*path, "/");
	*path = ft_strjoin(temp, pdirent->d_name);
	if (temp)
		free(temp);
}

void	free_exec_arg(char **path, char ***args, char ***envp, int is_executbl)
{
	if (*path && !is_executbl)
		free(*path);
	if (*args)
		dbl_array_clear(*args);
	if (*envp)
		dbl_array_clear(*envp);
}

char	**fill_envp(t_env *env, t_shell *shell)
{
	char	**envp;
	int		i;
	char	*temp;

	envp = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
	mem_check(shell, envp);
	i = 0;
	temp = NULL;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		if (env->value)
			envp[i++] = ft_strjoin(temp, env->value);
		else
			envp[i++] = temp;
		if (temp && env->value)
			free(temp);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	check_access(char **path, int *has_right)
{
	if (access(*path, X_OK) == 0)
	{
		*has_right = 1;
		return (1);
	}
	else
	{
		if (*path)
		{
			free(*path);
			*path = NULL;
			*has_right = 0;
		}
		return (0);
	}
}

int	check_executable(t_shell *shell, t_pars **cmd_parsed, char **path)
{
	*path = (*cmd_parsed)->value;
	if (access(*path, X_OK) != 0)
	{
		shell->cmd.exit_status = 126;
		ft_putstr_fd("Permission denied\n", 2);
		return (0);
	}
	return (1);
}
