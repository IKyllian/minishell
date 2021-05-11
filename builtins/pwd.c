/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:43 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/11 10:58:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_pwd(t_cmd *cmd)
{
	char	path[PATH_MAX];

	errno = 0;
	if (getcwd(path, PATH_MAX))
		ft_putstr_fd(path, cmd->fd);
	else
	{
		print_error(errno);
		cmd->exit_status = 1;
		return (1);
	}
	ft_putchar_fd('\n', cmd->fd);
	cmd->exit_status = 0;
	return (0);
}
