/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:37:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/21 16:33:02 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	next_cmd(t_pars **parsed)
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
		if (check_redirect(shell, parsed, shell->cmd.index_pipe) > 0)
			cmd_to_exec(shell, parsed);
	}
}

void	fork_pipe(int in, int out, t_shell *shell, t_pars **parsed, int nb_pipe)
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
		if (shell->cmd.index_pipe == nb_pipe)
		{
			if (dup2(in, shell->cmd.fd_in) == -1)
				print_error(errno);
		}
		else
		{
			if (dup2(in, shell->cmd.fd_in) == -1)
				print_error(errno);
			if (dup2(out, shell->cmd.fd_out) == -1)
				print_error(errno);
		}
		exec_child(shell, parsed);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (g_pids.pid[shell->cmd.index_pipe].is_heredoc)
		waitpid(pid, &pid, 0);
	g_pids.pid[shell->cmd.i_pids++].pid = pid;
}

void	exec_pipe(t_shell *shell, t_pars **parsed, int nb_pipe)
{
	int		pipefd[2];
	int		in;

	in = shell->cmd.fd_in;
	while (shell->cmd.index_pipe < nb_pipe)
	{
		errno = 0;
		if (pipe(pipefd) == -1)
			print_error(errno);
		fork_pipe(in, pipefd[1], shell, parsed, nb_pipe); // Execute la commande a gauche du pipe
		if (in)
			close(in);
		in = pipefd[0];
		close(pipefd[1]);
		next_cmd(parsed);
		shell->cmd.index_pipe++;
	}
	if (in)
	{
		fork_pipe(pipefd[0], 1, shell, parsed, nb_pipe);
		close(in);
		while (wait(NULL) != -1) ;
	}
}

int	pipe_count(t_pars *parsed)
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

void	set_heredoc_check(t_pars *parsed, int count)
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
	int	count;

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
