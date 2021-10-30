/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:39:31 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 12:48:05 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_flag(t_pars *cmd_parsed, int *flag_exist, int is_first, int *skip)
{
	int	has_dash;
	int	has_n;
	int	i;

	has_dash = 0;
	has_n = 0;
	i = 0;
	while (cmd_parsed->value[i])
	{
		if (i == 0 && cmd_parsed->value[i] == '-')
			has_dash = 1;
		else if ((i == 0 && cmd_parsed->value[i] != '-')
			|| cmd_parsed->value[i] != 'n')
		{
			*skip = 0;
			return (0);
		}
		if (cmd_parsed->value[i++] == 'n')
			has_n = 1;
	}
	if (has_n && has_dash && is_first)
		*flag_exist = 1;
	if (has_n && has_dash && *flag_exist && *skip)
		return (1);
	return (0);
}

void	print_echo(t_shell *shell, t_pars **cmd_parsed)
{
	if ((*cmd_parsed)->value[0] == '$' && (*cmd_parsed)->value[1] == '?')
		ft_putnbr_fd(shell->cmd.exit_status, shell->cmd.fd_out);
	else
		ft_putstr_fd((*cmd_parsed)->value, shell->cmd.fd_out);
	if ((*cmd_parsed)->next && (*cmd_parsed)->next->type == 2)
		ft_putchar_fd(' ', shell->cmd.fd_out);
}

int	ft_echo(t_shell *shell, t_pars **cmd_parsed)
{
	int	flag_exist;
	int	skip;

	flag_exist = 0;
	skip = 1;
	if ((*cmd_parsed)->next != NULL)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		check_flag((*cmd_parsed), &flag_exist, 1, &skip);
		while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
		{
			if (check_flag((*cmd_parsed), &flag_exist, 0, &skip) == 0)
				print_echo(shell, cmd_parsed);
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
	}
	if (!flag_exist)
		ft_putchar_fd('\n', shell->cmd.fd_out);
	return (0);
}
