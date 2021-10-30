/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 08:34:30 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 14:01:12 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	end_cd(t_shell *shell, t_pars **cmd_parsed)
{
	if (errno != 14)
		print_error(errno);
	shell->cmd.exit_status = 1;
	(*cmd_parsed) = (*cmd_parsed)->next;
	return (1);
}

int	get_nb(char *str, int i, int *nb)
{
	int	space;

	space = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			space = 1;
			i++;
			continue ;
		}
		if ((!(str[i] >= 48 && str[i] <= 57))
			|| ((str[i] >= 48 && str[i] <= 57) && space))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(&str[i], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		*nb = (*nb * 10) + (str[i++] - 48);
	}
	return (0);
}
