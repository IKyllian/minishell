/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:46:40 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/06 10:07:41 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokenizer(t_cmd *cmd, char *line)
{
	int	i;
	int	j;
	int t;

	if (line && !line[0])
		return (0);
	cmd->dquote = 0;
	cmd->squote = 0;
	i = 0;
	j = dbl_array_len(cmd->history) - 1;
	t = 0;
	while (cmd->history[j][i])
	{
		check_quote(cmd, cmd->history[j], i, 0);
		if (cmd->dquote || cmd->squote)
		{
			i++;
			t++;
			continue ;
		}
		if (t == 1 && i >= 1 /*&& is_operator(cmd->history[j][i - 1])*/
			&& is_long_operator(cmd->history[j][i], cmd->history[j][i - 1]))
		{
			if (i >= 1 && cmd->history[j][i - 1] != ' ')
				lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t + 1)));
			if (cmd->history[j][i] == ' ')
				i += 1;
			t = 0;
		}
		else if (t == 1 && i >= 1 && is_operator(cmd->history[j][i - 1])
			&& !is_long_operator(cmd->history[j][i], cmd->history[j][i - 1]))
		{
			if (i >= 1 && cmd->history[j][i - 1] != ' ')
				lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
			if (cmd->history[j][i] == ' ')
				t = 0;
			else
				t = 1;
		}
		else if (is_operator(cmd->history[j][i]))
		{
			if (i >= 1 && cmd->history[j][i - 1] != ' ' && t > 0)
				lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
			t = 1;
		}
		else if (cmd->history[j][i] == '\n')
		{
			if (i >= 1 && cmd->history[j][i - 1] != ' ')
				lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
			t = 0;
		}
		else if (cmd->history[j][i] == ' ')
		{
			if (i >= 1 && cmd->history[j][i - 1] != ' ' && t != 0)
				lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
			t = 0;
		}
		else
			t++;
		i++;
	}
	if (t == 0)
	{
		// printf("i%i, empty\n", i);
		// if (i >= 1 && cmd->history[j][i - 1] != ' ')
		// 	lstaddback_pars(&cmd->parsed, lstnew_pars(&cmd->history[j][i]));
		return (0);
	}
	else
	{
		// printf("i%i, all\n", i);
		if (i >= 1 && (cmd->history[j][i - 1] != ' ' || (cmd->squote || cmd->dquote)))
			lstaddback_pars(&cmd->parsed, lstnew_pars(ft_strndup(&cmd->history[j][i - t], t)));
		return (0);
	}
	return (0);
}