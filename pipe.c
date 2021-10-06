/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:37:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/06 14:35:18 by kdelport         ###   ########.fr       */
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
		check_cmd_arg(shell, parsed);
}

void exec_last_pipe(t_shell *shell, t_pars **parsed, int pipefd[2], pid_t *pid2)
{
	*pid2 = fork();
	if (*pid2 == -1)
		print_error(errno);
	else if (*pid2 == 0)
	{
		if (dup2(pipefd[0], shell->cmd.fd_in) == -1)
			print_error(errno);
		close(pipefd[1]);
		close(pipefd[0]);
		next_cmd(parsed);
		if ((*parsed))
			check_cmd_arg(shell, parsed);
		exit(1);
	}
	shell->cmd.pids[shell->cmd.i_pids].pid = *pid2;
	shell->cmd.i_pids++;
}

pid_t first_fork(t_shell *shell, t_pars **parsed, int pipefd[2], int *fdd)
{
	pid_t	pid;
	
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
	shell->cmd.pids[shell->cmd.i_pids].pid = pid;
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
			exec_last_pipe(shell, parsed, pipefd, &pid2); // Execute la commande a droite du pipe
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		if (count == nb_pipe - 1)
			waitpid(pid2, NULL, 0);
		fdd = pipefd[0];
		count++;
		next_cmd(parsed);
	}
}

int pipe_count(t_pars *parsed)
{
	t_pars	*check;
	int		count;

	check = parsed;
	count = 0;
	while (check)
	{
		if (check->type == 3)
			count++;
		check = check->next;
	}
	return (count);
}

int	check_pipe(t_pars **parsed, t_shell *shell)
{
	int count;

	count = pipe_count((*parsed));
	if (count > 0)
	{
		shell->cmd.pids = malloc(sizeof(pid_t) * (count + 2));
		exec_pipe(shell, parsed, count);
		return (1);
	}
	return (0);
}
