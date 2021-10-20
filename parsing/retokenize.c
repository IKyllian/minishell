/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 08:45:13 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/20 09:22:47 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	retype(t_pars *new_tokens)
{
	t_pars	*lst;

	lst = new_tokens;
	while (lst)
	{
		lst->type = 2;
		lst = lst->next;
	}
}

int	check_sub(t_cmd *cmd, char *str, t_pars **new_tokens)
{
	int	i;
	int	j;

	cmd->dquote = 0;
	cmd->squote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		check_quote(cmd, str, i, 0);
		if (cmd->squote || cmd->dquote)
		{
			i++;
			continue ;
		}
		if (str[i] == ' ')
		{
			if (str[i - 1] != ' ')
				lstaddback_pars(new_tokens, lstnew_pars(ft_strndup(&str[j], i - j)));
			j = i + 1;
		}
		i++;
	}
	if (j == 0)
		return (0);
	else
	{
		if (str[i - 1] != ' ')
			lstaddback_pars(new_tokens, lstnew_pars(ft_strndup(&str[j], i - j)));
	}
	retype(*new_tokens);
	return (1);
}

t_pars	*retokenize(t_cmd *cmd, t_pars **token, int *t)
{
	int		i;
	t_pars	*lst;
	t_pars	*new_tokens;

	i = 0;
	lst = cmd->parsed;
	new_tokens = NULL;
	if (!check_sub(cmd, (*token)->value, &new_tokens))
	{
		*t += 1;
		return ((*token)->next);
	}
	if (i == *t)
		return (lst_replace_start(cmd, new_tokens, t));
	while (lst)
	{
		if (i == *t - 1)
			return (lst_replace(lst, new_tokens, t));
		lst = lst->next;
		i++;
	}
	return ((*token)->next);
}
