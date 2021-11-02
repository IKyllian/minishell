/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:46:40 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 15:04:50 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delimiter(t_shell *shell, int *i, int *j, int *t)
{
	if (*t == 1 && *i >= 1
		&& is_long_operator(shell->cmd.history[*j][*i], \
		shell->cmd.history[*j][*i - 1]))
		long_operator(shell, i, j, t);
	else if (*t == 1 && *i >= 1 && is_operator(shell->cmd.history[*j][*i - 1])
		&& !is_long_operator(shell->cmd.history[*j][*i], \
		shell->cmd.history[*j][*i - 1]))
		short_operator(shell, i, j, t);
	else if (is_operator(shell->cmd.history[*j][*i]))
		operator(shell, i, j, t);
	else if (shell->cmd.history[*j][*i] == '\n')
		endofline(shell, i, j, t);
	else if (shell->cmd.history[*j][*i] == ' ')
		space(shell, i, j, t);
	else
		*t += 1;
	*i += 1;
}

int	token_creator(t_shell *shell, int *i, int *j, int *t)
{
	check_quote(&shell->cmd, shell->cmd.history[*j], *i, 0);
	if (shell->cmd.dquote || shell->cmd.squote)
	{
		*i += 1;
		*t += 1;
		return (1);
	}
	delimiter(shell, i, j, t);
	return (0);
}

int	tokenizer(t_cmd *cmd, char *line, t_shell *shell)
{
	int	i;
	int	j;
	int	t;

	if (line && !line[0])
		return (0);
	cmd->dquote = 0;
	cmd->squote = 0;
	i = 0;
	j = dbl_array_len(cmd->history) - 1;
	t = 0;
	while (cmd->history[j][i])
		if (token_creator(shell, &i, &j, &t))
			continue ;
	if (t == 0)
		return (0);
	else
	{
		if (i >= 1 && (cmd->history[j][i - 1] != ' '
			|| (cmd->squote || cmd->dquote)))
			lstaddback_pars(&cmd->parsed,
				lstnew_pars(ft_strndup(&cmd->history[j][i - t], t), shell));
		return (0);
	}
	return (0);
}
