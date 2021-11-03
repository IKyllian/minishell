/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 08:24:19 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *shell, t_pars **cmd_parsed)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->name, shell->cmd.fd_out);
			ft_putchar_fd('=', shell->cmd.fd_out);
			ft_putstr_fd(env->value, shell->cmd.fd_out);
			ft_putchar_fd('\n', shell->cmd.fd_out);
		}
		env = env->next;
	}
	(*cmd_parsed) = (*cmd_parsed)->next;
	shell->cmd.exit_status = 0;
	return (0);
}
