/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/26 12:39:40 by kdelport         ###   ########lyon.fr   */
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

int	ft_redirect_in(t_cmd *cmd, t_pars **cmd_parsed)
{
	int	fd;

	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	else
		return (0);
	fd = -1;
	close(cmd->fd_in);
	fd = open((*cmd_parsed)->value, O_CREAT | O_RDONLY, S_IRWXU);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	if (dup2(fd, cmd->fd_in) == -1)
		print_error(errno);
	return (1);
}	

int	ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed)
{
	int	fd;

	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	else
		return (0);
	fd = -1;
	close(cmd->fd_out);
	if (ft_strcmp(redirect, ">>") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (ft_strcmp(redirect, ">") == 0)
		fd = open((*cmd_parsed)->value, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
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