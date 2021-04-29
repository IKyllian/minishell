/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/29 13:00:56 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Exit status = 0 if no error
int	ft_env(t_env *env, t_cmd *cmd)
{
	while (env)
	{
		if (env->value != NULL)
		{
			ft_putstr_fd(env->name, cmd->fd);
			ft_putchar_fd('=', cmd->fd);
			ft_putstr_fd(env->value, cmd->fd);
			ft_putchar_fd('\n', cmd->fd);
		}
		env = env->next;
	}
	return (0);
}
