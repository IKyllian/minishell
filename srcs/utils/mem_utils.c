/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:47:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{
	free_redir(shell);
	if (shell->cmd.pids->pid)
	{
		free(shell->cmd.pids->pid);
		shell->cmd.pids->pid = NULL;
		free(shell->cmd.pids);
	}
	if (shell->line)
		free(shell->line);
	free(shell->cmd.prompt);
	free(shell->cmd.pids);
	lstclear_pars(&shell->cmd.parsed);
	lstclear_env(&shell->env);
	dbl_array_clear(shell->cmd.history);
}

void	mem_check(void *ptr)
{
	if (!ptr)
		exit(-12);
}
