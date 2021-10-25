/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/22 12:24:05 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	restore_cmd(t_shell *shell)
{
	close(shell->cmd.fd_in);
	close(shell->cmd.fd_out);
	if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
		print_error(errno);
	if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
		print_error(errno);
	shell->cmd.is_heredoc = 0;
	shell->cmd.i_redir = 0;
	shell->cmd.index_pipe = 0;
	shell->cmd.i_pids = 0;
	shell->cmd.hd_has_error = 0;
	if (shell->cmd.redir)
	{
		free(shell->cmd.redir);
		shell->cmd.redir = NULL;
	}
	if (g_pids.pid)
	{
		free(g_pids.pid);
		g_pids.pid = NULL;
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
	return (1);
}

int is_last_heredoc(t_shell *shell)
{
	int i;

	i = 0;
	while (i <= g_pids.count)
	{
		if (i > shell->cmd.index_pipe)
		{
			if (g_pids.pid[i].is_heredoc == 1)
				return (0);
		}
		i++;
	}
	return (1);
}

void	fill_arg_hd(t_pars **cmd_parsed, t_pars	**args, int *cmd_exit)
{
	t_pars	*cmd;

	cmd = NULL;
	if ((*cmd_parsed)->type == 1)
	{
		*cmd_exit = 1;
		*args = lstnew_pars((*cmd_parsed)->value);
		cmd = (*cmd_parsed);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		lstaddback_pars(args, lstnew_pars((*cmd_parsed)->value));
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	if (ft_strcmp(cmd->value, "echo") == 0)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		(*cmd_parsed) = (*cmd_parsed)->next;
		while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
		{
			lstaddback_pars(args, lstnew_pars((*cmd_parsed)->value));
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
	}
}

int	ft_heredoc(t_shell *shell, t_pars **cmd_parsed)
{
	t_pars	*args;
	int		fd;
	int		command_exist;

	command_exist = 0;
	if (shell->cmd.hd_has_error)
		return (-1);
	else if (!is_last_heredoc(shell))
		return (0);
	shell->cmd.is_heredoc = 1;
	fill_arg_hd(cmd_parsed, &args, &command_exist);
	fd = open("heredoc.txt", O_RDWR, 0777);
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	if (command_exist)
		cmd_to_exec(shell, &args);
	close(STDIN_FILENO);
	close(fd);
	unlink("heredoc.txt");
	return (0);
}