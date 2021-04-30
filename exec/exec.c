/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:19:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/30 15:35:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_in_dir(char **arg, char **path_split, int i)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	char			*temp;
	char			*path;

	pdir = opendir(path_split[i]);
	path = NULL;
	if (pdir == NULL)
		printf("Error\nCan't open directory : %s\n", path_split[i]);
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		if (ft_strcmp(pdirent->d_name, arg[0]) == 0)
		{
			path = path_split[i];
			temp = ft_strjoin(path, "/");
			path = ft_strjoin(temp, pdirent->d_name);
			if (temp)
				free(temp);
			break ;
		}
		pdirent = readdir(pdir);
	}
	closedir(pdir);
	return (path);
}

char	*search_path(t_env *env_path, char **arg)
{
	char			**path_split;
	int				i;
	char			*path;

	if (env_path == NULL)
		return (NULL);
	i = -1;
	path_split = ft_split(env_path->value, ':');
	path = NULL;
	while (path_split[++i])
	{
		path = search_in_dir(arg, path_split, i);
		if (path != NULL)
			break ;
	}
	free_tab(path_split);
	return (path);
}

void	ft_exec(t_env *env, char **arg)
{
	char	*path;
	pid_t	pid;
	// char	**envp;

	path = search_path(srch_and_return_env_var(env, "PATH"), arg);
	if (path == NULL)
		return ;
	pid = fork();
	if (pid == 0)
		execve(path, arg, NULL);
	else
	{
		wait(NULL);
	}
	if (path)
		free(path);
}