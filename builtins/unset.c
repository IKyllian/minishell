/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:23 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/22 13:46:49 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_shell *shell, t_pars **cmd_parsed)
{
	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2) // Si le type est un argument
	{
		srch_and_dlt_env_var(shell->env, (*cmd_parsed)->value);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	if ((*cmd_parsed) && ft_strcmp((*cmd_parsed)->value, "unset") == 0)
		(*cmd_parsed) = (*cmd_parsed)->next;
	return (0);
}