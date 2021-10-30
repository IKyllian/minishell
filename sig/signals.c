/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/30 08:41:53 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	p_sigkill(int sig)
{
	(void)sig;
	g_heredoc = 1;
	ft_putchar_fd('\n', 2);
}

void	p_sigquit(int sig)
{
	(void)sig;
	g_heredoc = 2;
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
}

void	f_sigkill(int sig)
{
	(void)sig;
	exit(130);
}

void	f_sigquit(int sig)
{
	(void)sig;
	exit(131);
}

void	m_sigkill(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
