/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/22 12:22:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(char *str)
{
	char *env_var;
	int	flag_exist;

	flag_exist = 0;
	if (str)
	{
		if (str[0] != '$')
			ft_putstr_fd(str, 1);
		else
		{
			if (str[1] == ' ')
				ft_putstr_fd(str, 1);
			else
			{
				env_var = getenv(str + 1);
				if (env_var != NULL)
					ft_putstr_fd(env_var, 1);
			}
		} 
	}
	if (!flag_exist)
		ft_putchar_fd('\n', 1);
	return (1);
}