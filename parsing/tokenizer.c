/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:46:40 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/30 13:04:07 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delimiter(t_cmd *cmd, int *i, int *j, int *t)
{
	if (*t == 1 && *i >= 1
		&& is_long_operator(cmd->history[*j][*i], cmd->history[*j][*i - 1]))
		long_operator(cmd, i, j, t);
	else if (*t == 1 && *i >= 1 && is_operator(cmd->history[*j][*i - 1])
		&& !is_long_operator(cmd->history[*j][*i], cmd->history[*j][*i - 1]))
		short_operator(cmd, i, j, t);
	else if (is_operator(cmd->history[*j][*i]))
		operator(cmd, i, j, t);
	else if (cmd->history[*j][*i] == '\n')
		endofline(cmd, i, j, t);
	else if (cmd->history[*j][*i] == ' ')
		space(cmd, i, j, t);
	else
		*t += 1;
	*i += 1;
}

int	token_creator(t_cmd *cmd, int *i, int *j, int *t)
{
	check_quote(cmd, cmd->history[*j], *i, 0);
	if (cmd->dquote || cmd->squote)
	{
		*i += 1;
		*t += 1;
		return (1);
	}
	delimiter(cmd, i, j, t);
	return (0);
}

int	tokenizer(t_cmd *cmd, char *line)
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
		if (token_creator(cmd, &i, &j, &t))
			continue ;
	if (t == 0)
		return (0);
	else
	{
		if (i >= 1 && (cmd->history[j][i - 1] != ' '
			|| (cmd->squote || cmd->dquote)))
			lstaddback_pars(&cmd->parsed,
				lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
		return (0);
	}
	return (0);
}
