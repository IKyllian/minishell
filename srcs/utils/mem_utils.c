/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:47:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 13:46:08 by kdelport         ###   ########.fr       */
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

void	mem_check(t_shell *shell, void *ptr)
{
	if (!ptr)
	{
		free_all(shell);
		while (1) ;
		exit(1);
	}
}
