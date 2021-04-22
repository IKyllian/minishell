/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/22 16:48:07 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(const char *path, t_env *env)
{
	char old_path[PATH_MAX];

	getcwd(old_path, PATH_MAX);
	errno = 0;
	if (chdir(path) == 0)
	{
		if (env->old_path_index == -1)
			add_env_var(env, "OLDPWD=", old_path);
		else
			change_env_var(env, "OLDPWD=", old_path);
		return (1);
	}
	else
		print_error(errno);
	return (0);
}