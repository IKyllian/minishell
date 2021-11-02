/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_shell *shell, t_pars **parsed, int index_cmd)
{
	int	first_index;
	int	ret;

	first_index = 0;
	ret = 1;
	while (shell->cmd.redir[shell->cmd.i_redir].value != NULL
		&& shell->cmd.redir[shell->cmd.i_redir].pipe_index <= index_cmd)
	{
		if (shell->cmd.redir[shell->cmd.i_redir].pipe_index == index_cmd)
		{
			if (shell->cmd.redir[shell->cmd.i_redir].type == 1)
				ret = ft_redirect_in(&shell->cmd, \
					shell->cmd.redir[shell->cmd.i_redir]);
			else
				ret = ft_redirect(&shell->cmd, \
					shell->cmd.redir[shell->cmd.i_redir]);
		}
		shell->cmd.i_redir++;
	}
	return (check_heredoc(shell, parsed, ret));
}

void	reset_var(t_shell *shell)
{
	shell->cmd.is_heredoc = 0;
	shell->cmd.i_redir = 0;
	shell->cmd.index_pipe = 0;
	shell->cmd.i_pids = 0;
	shell->cmd.hd_has_error = 0;
	shell->cmd.nbr_pipe = 0;
	shell->cmd.mode_export = 0;
	shell->cmd.is_pipe = 0;
}

void	restore_cmd(t_shell *shell)
{
	close(shell->cmd.fd_in);
	close(shell->cmd.fd_out);
	if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
		print_error(errno);
	if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
		print_error(errno);
	reset_var(shell);
	free_redir(shell);
	if (shell->cmd.pids->pid)
	{
		free(shell->cmd.pids->pid);
		shell->cmd.pids->pid = NULL;
	}
	if (shell->line)
		free(shell->line);
	lstclear_pars(&shell->cmd.parsed);
}

int	ft_redirect_in(t_cmd *cmd, t_redir redir)
{
	int	fd;

	fd = -1;
	fd = open(redir.value, O_RDONLY, S_IRWXU);
	errno = 0;
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir.value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	close(cmd->fd_in);
	if (dup2(fd, cmd->fd_in) == -1)
		print_error(errno);
	close(fd);
	return (1);
}

int	ft_redirect(t_cmd *cmd, t_redir redir)
{
	int	fd;

	fd = -1;
	if (redir.type == 3)
		fd = open(redir.value, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (redir.type == 2)
		fd = open(redir.value, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	errno = 0;
	if (fd == -1)
	{
		print_error(errno);
		return (0);
	}
	close(cmd->fd_out);
	if (dup2(fd, cmd->fd_out) == -1)
		print_error(errno);
	close(fd);
	return (1);
}
