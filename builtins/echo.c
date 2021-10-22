/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/22 09:01:16 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Exit status = 0 if no error
int	ft_echo(t_shell *shell, t_pars **cmd_parsed)
{
	int		flag_exist;

	flag_exist = 0;
	if ((*cmd_parsed)->next != NULL)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		if (ft_strcmp((*cmd_parsed)->value, "-n") == 0)
		{
			flag_exist = 1;
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
		while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
		{
			if ((*cmd_parsed)->value[0] == '$' && (*cmd_parsed)->value[1] == '?')
				ft_putnbr_fd(shell->cmd.exit_status, shell->cmd.fd_out);
			else
				ft_putstr_fd((*cmd_parsed)->value, shell->cmd.fd_out);
			if ((*cmd_parsed)->next && (*cmd_parsed)->next->type == 2)
				ft_putchar_fd(' ', shell->cmd.fd_out);
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
	}
	if (!flag_exist)
		ft_putchar_fd('\n', shell->cmd.fd_out);
	return (0);
}
