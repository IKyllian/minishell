/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/30 16:03:05 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Exit status = 0 if no error
int	ft_env(t_shell *shell)
{
	while (shell->env)
	{
		if (shell->env->value != NULL)
		{
			ft_putstr_fd(shell->env->name, shell->cmd.fd);
			ft_putchar_fd('=', shell->cmd.fd);
			ft_putstr_fd(shell->env->value, shell->cmd.fd);
			ft_putchar_fd('\n', shell->cmd.fd);
		}
		shell->env = shell->env->next;
	}
	return (0);
}
