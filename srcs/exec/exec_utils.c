/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 08:30:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
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

char	**fill_envp(t_env *env)
{
	char	**envp;
	int		i;
	char	*temp;

	envp = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
	i = 0;
	temp = NULL;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		envp[i++] = ft_strjoin(temp, env->value);
		if (temp)
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