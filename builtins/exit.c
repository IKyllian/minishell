/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 12:46:41 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int	space;

	i = 0;
	nb = 0;
	sign = 1;
	space = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
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
			return (300);
		}
		nb = (nb * 10) + (str[i++] - 48);
	}
	return (exit_nbr_caster(nb * sign));
}

int	get_exit_nb(t_shell *shell, t_pars **cmd_parsed)
{
	int	nb;

	nb = 0;
	if ((*cmd_parsed)->next
		&& ((*cmd_parsed)->next->next && (*cmd_parsed)->next->next->type == 2))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->cmd.exit_status = 1;
		return (301);
	}
	if ((*cmd_parsed)->next && (*cmd_parsed)->next->type == 2)
	{
		nb = num_is_valid((*cmd_parsed)->next->value);
		if (nb == 300)
		{
			nb = 255;
			return (nb);
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
