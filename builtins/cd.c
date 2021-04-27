/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:25 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/23 16:32:10 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// exit status = 0 if no error, >0 if an error occured
int	ft_cd(const char *path, t_env *env)
{
	char old_path[PATH_MAX];
	char *dup_path;

	// getcwd(old_path, PATH_MAX);
	errno = 0;
	if (chdir(path) == 0)
	{
		// srch_and_rplce_env_var(env, "OLDPWD", old_path);
		getcwd(old_path, PATH_MAX);
		dup_path = ft_strdup(old_path); // Obligé de Dup pour pouvoir free plus tard dans la prochaine fonction
		srch_and_rplce_env_var(env, "PWD", dup_path);
		return (0);
	}
	else
	{
		print_error(errno);
		return (1);
	}
}