/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:17:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/20 13:13:12 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	restore_cmd(t_shell *shell)
{
// probably old branch
//     if (dup2(shell->cmd.fd_stdin, shell->cmd.fd_in) == -1)
//         print_error(errno);
//     if (dup2(shell->cmd.fd_stdout, shell->cmd.fd_out) == -1)
//         print_error(errno);
//     shell->cmd.is_heredoc = 0;
// 	if (shell->cmd.redir)
// 	{
// 		// printf("redirecting\n");
// 		free(shell->cmd.redir);
// 		// printf("redir done\n");
// 		shell->cmd.redir = NULL;
// 	}
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
		return (0);
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

void	execute_heredoc(t_shell *shell, char **exit_words, int size, int fd)
{
	char	*line;
	int		ret;
	int		i;

	i = 0;
	ret = 1;
	line = NULL;
	g_heredoc = 1;
	while (ret && g_heredoc)
	{
		ft_putstr_fd("> ", shell->cmd.fd_stdout);
		ret = ft_get_next_line(shell->cmd.fd_stdin, 2, &line);
		if (i == size - 1 && ft_strcmp(line, exit_words[i]) != 0)
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		if (ft_strcmp(line, exit_words[i]) == 0)
		{
			if (i++ == size - 1)
				break ;
		}
		free(line);
		line = NULL;
	}
	if (line && g_heredoc)
		free(line);
}

int	ft_heredoc(t_shell *shell, t_pars **cmd_parsed,
	char **exit_words, int size)
{
	t_pars	*args;
	int		fd;
	int		command_exist;

	command_exist = 0;
	if (!exit_words[size - 1])
	{
		ft_putstr_fd("Error : No exit word\n", shell->cmd.fd_out);
		return (-1);
	}
	shell->cmd.is_heredoc = 1;
	fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if ((*cmd_parsed)->type == 1)
	{
		command_exist = 1;
		args = lstnew_pars((*cmd_parsed)->value);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		lstaddback_pars(&args, lstnew_pars((*cmd_parsed)->value));
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	execute_heredoc(shell, exit_words, size, fd);
	close(fd);
	if (!g_heredoc)
	{
		unlink("heredoc.txt");
		// g_heredoc = 1;
		return (0);
	}
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
