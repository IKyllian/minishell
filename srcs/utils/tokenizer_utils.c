/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 08:18:29 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 13:50:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	long_operator(t_shell *shell, int *i, int *j, int *t)
{
	if (*i >= 1 && shell->cmd.history[*j][*i - 1] != ' ')
		lstaddback_pars(&shell->cmd.parsed,
			lstnew_pars(ft_strndup(&shell->cmd.history[*j][*i - *t], *t + 1), \
			shell));
	if (shell->cmd.history[*j][*i] == ' ')
		*i += 1;
	*t = 0;
}

void	short_operator(t_shell *shell, int *i, int *j, int *t)
{
	if (*i >= 1 && shell->cmd.history[*j][*i - 1] != ' ')
		lstaddback_pars(&shell->cmd.parsed,
			lstnew_pars(ft_strndup(&shell->cmd.history[*j][*i - *t], *t), \
			shell));
	if (shell->cmd.history[*j][*i] == ' ')
		*t = 0;
	else
		*t = 1;
}

void	operator(t_shell *shell, int *i, int *j, int *t)
{
	if (*i >= 1 && shell->cmd.history[*j][*i - 1] != ' ' && *t > 0)
		lstaddback_pars(&shell->cmd.parsed,
			lstnew_pars(ft_strndup(&shell->cmd.history[*j][*i - *t], *t), \
			shell));
	*t = 1;
}

void	endofline(t_shell *shell, int *i, int *j, int *t)
{
	if (*i >= 1 && shell->cmd.history[*j][*i - 1] != ' ')
		lstaddback_pars(&shell->cmd.parsed,
			lstnew_pars(ft_strndup(&shell->cmd.history[*j][*i - *t], *t), \
			shell));
	*t = 0;
}

void	space(t_shell *shell, int *i, int *j, int *t)
{
	if (*i >= 1 && shell->cmd.history[*j][*i - 1] != ' ' && *t != 0)
		lstaddback_pars(&shell->cmd.parsed,
			lstnew_pars(ft_strndup(&shell->cmd.history[*j][*i - *t], *t), \
			shell));
	*t = 0;
}
