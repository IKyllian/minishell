/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:23 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/29 09:59:31 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_env *env, char **arg)
{
	srch_and_dlt_env_var(env, arg[1]);
	return (0);
}
