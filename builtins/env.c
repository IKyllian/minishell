/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/11 16:30:38 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Exit status = 0 if no error
int	ft_env(t_shell *shell)
{
	t_env *env;

	env = shell->env;
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->name, shell->cmd.fd);
			ft_putchar_fd('=', shell->cmd.fd);
			ft_putstr_fd(env->value, shell->cmd.fd);
			ft_putchar_fd('\n', shell->cmd.fd);
		}
		env = env->next;
	}
	shell->cmd.exit_status = 0;
	return (0);
}
