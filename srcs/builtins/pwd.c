/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:43 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_pars **cmd_parsed)
{
	char	path[PATH_MAX];

	errno = 0;
	if (getcwd(path, PATH_MAX))
		ft_putstr_fd(path, cmd->fd_out);
	else
	{
		print_error(errno);
		cmd->exit_status = 1;
		return (1);
	}
	ft_putchar_fd('\n', cmd->fd_out);
	(*cmd_parsed) = (*cmd_parsed)->next;
	cmd->exit_status = 0;
	return (0);
}
