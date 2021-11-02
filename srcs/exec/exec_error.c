/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:06:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 11:23:19 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_path_env(char **cmd_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*cmd_path, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

int	path_error(char *path, int has_right, int fd, char *cmd_path)
{
	if (path == NULL)
	{
		if (has_right)
		{
			ft_putstr_fd("minishell: ", fd);
			ft_putstr_fd(cmd_path, fd);
			ft_putstr_fd(": command not found\n", fd);
			return (127);
		}
		else
		{
			ft_putstr_fd("Permission denied\n", fd);
			return (126);
		}
	}
	return (0);
}

char	*error_pdir(char **join_path)
{
	ft_putstr_fd("Error\nCan't open directory : ", 2);
	ft_putstr_fd(*join_path, 2);
	ft_putstr_fd("\n", 2);
	free(*join_path);
	return (NULL);
}
