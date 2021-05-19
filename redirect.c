/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/19 14:56:34 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	restaure_fd(t_shell *shell)
{
	if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
		print_error(errno);
	if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
		print_error(errno);
}

int	ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed)
{
	int	fd;

	fd = -1;
	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	if (ft_strcmp(redirect, ">>") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 00777);
	else if (ft_strcmp(redirect, ">") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 00777);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	if (dup2(fd, cmd->fd_out) == -1)
		print_error(errno);
	return (1);
}