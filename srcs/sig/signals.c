/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 07:59:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/03 08:01:41 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_sigkill(int sig)
{
	(void)sig;
	g_heredoc = 1;
}

void	p_sigquit(int sig)
{
	(void)sig;
	g_heredoc = 2;
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
	g_heredoc = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
