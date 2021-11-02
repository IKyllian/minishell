/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 09:23:49 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/29 13:39:02 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	pipe_count(t_pars *parsed, t_cmd *cmd)
{
	t_pars	*check;

	check = parsed;
	cmd->pids->count = 0;
	while (check)
	{
		if (check->type == 3)
			cmd->pids->count++;
		check = check->next;
	}
	return (cmd->pids->count);
}

void	dup_pipe(t_shell *shell, int in, int out)
{
	if (shell->cmd.index_pipe == shell->cmd.nbr_pipe)
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
		close(shell->cmd.pipe_fd);
	}
}
