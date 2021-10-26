/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 09:59:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/26 11:13:16 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	num_is_valid(char *str)
{
	int	i;
	int nb;
	int is_neg;

	i = -1;
	nb = 0;
	is_neg = 0;
	while (str[++i])
	{
		if (i == 0 && str[i] == '-')
			is_neg = 1;
		else if (!(str[i] >= 48 && str[i] <= 57) && str[i] != ' ')
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd("str", 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (-2);
		}
		nb = (nb * 10) + (str[i] - 48);
	}
	if (is_neg || nb > 255)
		return (-1);
	return (nb);
}
// exit [n] exit status = if n specified exit status is n except if n is not an unsigned decimal integer
// or greater than 255, else the value of exit status is the value of the last command 

void	ft_exit(t_shell *shell, t_pars **cmd_parsed)
{
	int	nb;
	int ret;

	nb = 0;
	ret = 0;
	unset_term(shell);
	ft_putstr_fd("exit\n", 2);
	if (shell->line)
	{
		if ((*cmd_parsed)->next && (*cmd_parsed)->next->type == 2)// Si le type est un argument
		{
			nb = num_is_valid((*cmd_parsed)->next->value);
			if (nb == -1)
				ret = 252;
			else if (nb == -2)
				ret = 255;
		}
		if ((*cmd_parsed)->next && (*cmd_parsed)->next->next && nb != -2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			shell->cmd.exit_status = 1;
			return ;
		}
	}
	close(shell->cmd.fd_in);
	close(shell->cmd.fd_out);
	free(shell->cmd.prompt);
	free_parse_linked_list(shell->cmd.parsed);
	free_env_linked_list(shell->env);
	if (ret > 0)
		exit(ret);
	else
		exit (0);
}