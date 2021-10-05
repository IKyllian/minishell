/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:37:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/06/29 13:09:45 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	exec_parent(t_shell *shell, t_pars **parsed)
{
	while ((*parsed) && (*parsed)->type != 3)
		(*parsed) = (*parsed)->next;
	if ((*parsed) && (*parsed)->next)
		(*parsed) = (*parsed)->next;
	if ((*parsed))
		check_cmd_arg(shell, parsed);
	if ((*parsed) && (*parsed)->type == 3)
		exec_pipe(shell, parsed);
}

void	exec_child(t_shell *shell, t_pars **parsed)
{
	if ((*parsed) && (*parsed)->type == 3)
		(*parsed) = (*parsed)->next;
	if ((*parsed))
		check_cmd_arg(shell, parsed);
}

void	exec_pipe(t_shell *shell, t_pars **parsed)
{
	pid_t	pid;
	int		pipefd[2];

	errno = 0;
	if (pipe(pipefd) == -1)
		print_error(errno);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	else if (pid == 0)
	{
		if (dup2(pipefd[1], shell->cmd.fd_out) == -1)
			print_error(errno);
		close(pipefd[0]);
		exec_child(shell, parsed);
		close(pipefd[1]);
		exit(1);
	}
	else
	{
		if (dup2(pipefd[0], shell->cmd.fd_in) == -1)
			print_error(errno);
		close(pipefd[1]);
		exec_parent(shell, parsed);
		wait(NULL);
		close(pipefd[0]);
	}
}

int	check_pipe(t_pars **parsed_check, t_pars **parsed, t_shell *shell)
{
	while ((*parsed_check))
	{
		if ((*parsed_check)->type == 3)
		{
			exec_pipe(shell, parsed);
			(*parsed_check) = (*parsed_check)->next;
			return (1);
		}
		if ((*parsed_check)->type == 5)
		{
			(*parsed_check) = (*parsed_check)->next;
			return (0);
		}
		else
			(*parsed_check) = (*parsed_check)->next;
	}
	return (0);
}