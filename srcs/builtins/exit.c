/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 08:48:24 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_status(int status)
{
	if (g_heredoc == 1)
		return (130);
	else if (g_heredoc == 2)
		return (131);
	return (WEXITSTATUS(status));
}

int	exit_nbr_caster(int nb)
{
	if (nb >= 0)
		return (nb % 256);
	else
		return (256 + (nb % 256));
}

int	num_is_valid(char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (get_nb(str, i, &nb) == 255)
		return (255);
	return (exit_nbr_caster(nb * sign));
}

int	get_exit_nb(t_shell *shell, t_pars **cmd_parsed)
{
	int	nb;
	int	too_many_arg;

	nb = 0;
	if ((*cmd_parsed)->next
		&& ((*cmd_parsed)->next->next && (*cmd_parsed)->next->next->type == 2))
		too_many_arg = 1;
	else
		too_many_arg = 0;
	if ((*cmd_parsed)->next && (*cmd_parsed)->next->type == 2)
	{
		nb = num_is_valid((*cmd_parsed)->next->value);
		if (nb != 255 && too_many_arg)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->cmd.exit_status = 1;
			return (301);
		}
	}
	return (nb);
}

void	ft_exit(t_shell *shell, t_pars **cmd_parsed)
{
	int	ret;

	ret = 0;
	unset_term(shell);
	ft_putstr_fd("exit\n", 2);
	if (shell->line)
	{
		ret = get_exit_nb(shell, cmd_parsed);
		if (ret == 301)
			return ;
	}
	else
		ret = shell->cmd.exit_status;
	close(shell->cmd.fd_in);
	close(shell->cmd.fd_out);
	free_all(shell);
	exit(ret);
}
