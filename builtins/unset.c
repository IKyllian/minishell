/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:23 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 12:46:55 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_value(char c, int indx)
{
	if (((c >= 48 && c <= 57) || c == '=' || c == '+') && indx == 0)
		return (0);
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122) || (c == '_'))
		return (1);
	return (0);
}

int	check_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!is_valid_value(value[i], i))
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(value, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_shell *shell, t_pars **cmd_parsed)
{
	if ((*cmd_parsed)->next)
		(*cmd_parsed) = (*cmd_parsed)->next;
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		if (!check_value((*cmd_parsed)->value))
			return (1);
		srch_and_dlt_env_var(&shell->env, (*cmd_parsed)->value);
		if (ft_strcmp("PWD", (*cmd_parsed)->value) == 0)
			shell->cmd.set_old_to_null = 1;
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	if ((*cmd_parsed) && ft_strcmp((*cmd_parsed)->value, "unset") == 0)
		(*cmd_parsed) = (*cmd_parsed)->next;
	return (0);
}
