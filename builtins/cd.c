/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/05 13:17:22 by kdelport         ###   ########lyon.fr   */
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
		return ((char *)path);
}

int	ft_cd(const char *path, t_shell *shell)
{
	char	new_path[PATH_MAX];
	char	*dup_path;

	errno = 0;
	if (chdir(choose_path(path, shell->env)) == 0)
	{
		getcwd(new_path, PATH_MAX);
		dup_path = ft_strdup(new_path); // Obligé de Dup pour pouvoir free plus tard dans la prochaine fonction
		srch_and_rplce_env_var(shell->env, "PWD", dup_path);
		shell->cmd.exit_status = 0;
		return (0);
	}
	else
	{
		print_error(errno);
		shell->cmd.exit_status = 1;
		return (1);
	}
}