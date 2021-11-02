/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_current_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:02:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 11:07:49 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_dir_index(char **cmd_path)
{
	int	i;

	i = 0;
	while ((*cmd_path)[i])
		if ((*cmd_path)[i++] == '/')
			break ;
	return (i);
}

char	*search_dir(char **cmd_path)
{
	int		i;
	int		j;
	char	*dir;
	char	*cmd;

	i = get_dir_index(cmd_path);
	j = -1;
	cmd = NULL;
	if ((int)ft_strlen((*cmd_path)) == i)
		return (NULL);
	dir = malloc(sizeof(char) * (i + 1));
	mem_check(dir);
	dir[++j] = '/';
	while (++j < i)
		dir[j] = (*cmd_path)[j - 1];
	dir[j] = 0;
	j = 0;
	cmd = malloc(sizeof(char) * ((ft_strlen(*cmd_path) - i) + 1));
	mem_check(cmd);
	while ((*cmd_path)[i])
		cmd[j++] = (*cmd_path)[i++];
	cmd[j] = 0;
	free(*cmd_path);
	*cmd_path = cmd;
	return (dir);
}

int	join_pwd_path(char **cmd_path, char **join_path)
{
	char	path_pwd[PATH_MAX];
	char	*dir;
	char	*path;

	dir = search_dir(cmd_path);
	if (dir == NULL)
	{
		*join_path = NULL;
		return (1);
	}
	getcwd(path_pwd, PATH_MAX);
	path = ft_strjoin(path_pwd, dir);
	free(dir);
	*join_path = path;
	return (1);
}

char	*first_search(char **cmd_path, int *has_right)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	char			*path;
	char			*join_path;

	if (join_pwd_path(cmd_path, &join_path) && join_path == NULL)
		return (NULL);
	pdir = opendir(join_path);
	path = NULL;
	if (pdir == NULL)
		return (error_pdir(&join_path));
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		if (ft_strcmp(pdirent->d_name, *cmd_path) == 0)
		{
			join_exec_path(join_path, pdirent, &path);
			free(join_path);
			if (check_access(&path, has_right) == 1)
				break ;
		}
		pdirent = readdir(pdir);
	}
	closedir(pdir);
	return (path);
}
