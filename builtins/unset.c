/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:23 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/11 16:27:39 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	ft_unset(t_env *env, char **arg)
// {
// 	srch_and_dlt_env_var(env, arg[1]);
// 	return (0);
// }

int	ft_unset(t_shell *shell)
{
	t_pars	*cmd;

	cmd = shell->cmd.parsed;
	if (cmd->next)
		cmd = cmd->next;
	while (cmd && cmd->type == 2) // Si le type est un argument
	{
		srch_and_dlt_env_var(shell->env, cmd->value);
		cmd = cmd->next;
	}
	return (0);
}