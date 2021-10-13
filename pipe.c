/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:37:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/12 14:06:29 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void next_cmd(t_pars **parsed)
{
	while ((*parsed) && (*parsed)->type != 3)
		(*parsed) = (*parsed)->next;
	if ((*parsed) && (*parsed)->next)
		(*parsed) = (*parsed)->next;
}

void	exec_child(t_shell *shell, t_pars **parsed)
{
	if ((*parsed) && (*parsed)->type == 3)
		(*parsed) = (*parsed)->next;
	if ((*parsed))
	{
		if (check_redirect(shell, parsed) > 0)
			cmd_to_exec(shell, parsed);
	}
}

pid_t exec_last_pipe(t_shell *shell, t_pars **parsed, int pipefd[2])
{
	pid_t	pid;

	if (shell->cmd.i_pids > 0 
		&& g_pids.pid[shell->cmd.i_pids].is_heredoc == 1
		&& g_pids.pid[shell->cmd.i_pids - 1].is_heredoc == 1)
		waitpid(g_pids.pid[shell->cmd.i_pids - 1].pid, NULL, 0);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	else if (pid == 0)
	{
		if (dup2(pipefd[0], shell->cmd.fd_in) == -1)
			print_error(errno);
		close(pipefd[1]);
		close(pipefd[0]);
		next_cmd(parsed);
		if ((*parsed))
		{
			if (check_redirect(shell, parsed) > 0)
				cmd_to_exec(shell, parsed);
		}
		exit(1);
	}
	g_pids.pid[shell->cmd.i_pids].pid = pid;
	shell->cmd.i_pids++;
	return (pid);
}

pid_t first_fork(t_shell *shell, t_pars **parsed, int pipefd[2], int *fdd)
{
	pid_t	pid;
	
	if (shell->cmd.i_pids > 0 
		&& g_pids.pid[shell->cmd.i_pids].is_heredoc == 1
		&& g_pids.pid[shell->cmd.i_pids - 1].is_heredoc == 1)
		waitpid(g_pids.pid[shell->cmd.i_pids - 1].pid, NULL, 0);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	else if (pid == 0)
	{
		if (dup2(*fdd, shell->cmd.fd_in) == -1)
			print_error(errno);
		if (dup2(pipefd[1], shell->cmd.fd_out) == -1)
			print_error(errno);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_child(shell, parsed);
		exit(1);
	}
	g_pids.pid[shell->cmd.i_pids].pid = pid;
	shell->cmd.i_pids++;
	return (pid);
}

void	exec_pipe(t_shell *shell, t_pars **parsed, int nb_pipe)
{
	pid_t	pid;
    pid_t	pid2;
    int		pipefd[2];
	int		count;
	int		fdd;

	count = 0;
	fdd = shell->cmd.fd_in;
	while (count < nb_pipe)
	{
		errno = 0;
		if (pipe(pipefd) == -1)
			print_error(errno);
		pid = first_fork(shell, parsed, pipefd, &fdd); // Execute la commande a gauche du pipe
		if (count == nb_pipe - 1)
			pid2 = exec_last_pipe(shell, parsed, pipefd); // Execute la commande a droite du pipe
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		if (count == nb_pipe - 1)
			waitpid(pid2, NULL, 0);
		count++;
		if (count < nb_pipe)
			fdd = pipefd[0];
		else
			close(pipefd[0]);
		next_cmd(parsed);
	}
	signal(SIGQUIT, &p_sigquit);
	signal(SIGINT, &p_sigkill);
}

int pipe_count(t_pars *parsed)
{
	t_pars	*check;

	check = parsed;
	g_pids.count = 0;
	while (check)
	{
		if (check->type == 3)
			g_pids.count++;
		check = check->next;
	}
	return (g_pids.count);
}

void set_heredoc_check(t_pars *parsed, int count)
{
	t_pars	*check;
	int		i;

	check = parsed;
	i = 0;
	while (check)
	{
		if (check->type == 3)
			i++;
		else if (check->type == 4 && ft_strcmp(check->value, "<<") == 0)
			g_pids.pid[i].is_heredoc = 1;
		if (i > count)
			break;
		check = check->next;
	}
}

int	check_pipe(t_pars **parsed, t_shell *shell)
{
	int count;

	count = pipe_count((*parsed));
	if (count > 0)
	{
		g_pids.pid = malloc(sizeof(pid_t) * (count + 2));
		g_pids.mode = 2;
		set_heredoc_check((*parsed), count);
		exec_pipe(shell, parsed, count);
		return (1);
	}
	return (0);
}