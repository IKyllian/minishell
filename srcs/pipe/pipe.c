/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:37:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 08:04:05 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_pipe(int in, int out, t_shell *shell, t_pars **parsed)
{
	pid_t	pid;

	unset_term(shell);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	else if (pid == 0)
	{
		signal(SIGINT, f_sigkill);
		signal(SIGQUIT, f_sigquit);
		dup_pipe(shell, in, out);
		exec_child(shell, parsed);
		if (shell->cmd.exit_status > 0)
			exit(shell->cmd.exit_status);
		else
			exit(0);
	}
	signal(SIGINT, ign_sigkill);
	signal(SIGQUIT, ign_sigquit);
	if (shell->cmd.pids->pid[shell->cmd.index_pipe].is_heredoc)
		waitpid(pid, NULL, 0);
	shell->cmd.pids->pid[shell->cmd.i_pids++].pid = pid;
}

void	wait_childs(t_shell *shell)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i <= shell->cmd.nbr_pipe)
	{
		waitpid(shell->cmd.pids->pid[i].pid, &status, 0);
		i++;
	}
	if (!g_heredoc || !WEXITSTATUS(status))
		shell->cmd.exit_status = WEXITSTATUS(status);
	else if (g_heredoc == 1)
		shell->cmd.exit_status = 130;
	else if (g_heredoc == 2)
		shell->cmd.exit_status = 131;
	if (g_heredoc == 1)
		printf("\n");
	else if (g_heredoc == 2)
		printf("Quit: 3\n");
}

void	exec_pipe(t_shell *shell, t_pars **parsed)
{
	int		pipefd[2];
	int		in;

	in = shell->cmd.fd_in;
	while (shell->cmd.index_pipe < shell->cmd.nbr_pipe)
	{
		errno = 0;
		if (pipe(pipefd) == -1)
			print_error(errno);
		shell->cmd.pipe_fd = pipefd[0];
		fork_pipe(in, pipefd[1], shell, parsed);
		if (in)
			close(in);
		in = pipefd[0];
		close(pipefd[1]);
		next_cmd(parsed);
		shell->cmd.index_pipe++;
	}
	if (in)
	{
		fork_pipe(pipefd[0], 1, shell, parsed);
		close(in);
		close(pipefd[1]);
		wait_childs(shell);
	}
}

void	set_heredoc_check(t_pars *parsed, t_shell *shell, t_cmd *cmd)
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
			cmd->pids->pid[i].is_heredoc = 1;
		if (i > shell->cmd.nbr_pipe)
			break ;
		check = check->next;
	}
}

int	check_pipe(t_pars **parsed, t_shell *shell)
{
	shell->cmd.nbr_pipe = pipe_count((*parsed), &shell->cmd);
	if (shell->cmd.nbr_pipe > 0)
	{
		shell->cmd.is_pipe = 1;
		shell->cmd.pids->pid = ft_calloc((shell->cmd.nbr_pipe + 2), \
			sizeof(t_pid));
		set_heredoc_check((*parsed), shell, &shell->cmd);
		exec_pipe(shell, parsed);
		return (1);
	}
	return (0);
}
