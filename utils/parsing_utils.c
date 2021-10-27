/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:44:20 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 16:13:10 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_quote(t_cmd *cmd, char *src, int i, int mode)
{
	if (is_quote(src[i]))
	{
		if (src[i - 1] && src[i - 1] == '\\')
			return (src);
		if (src[i] == 34 && !cmd->squote)
		{
			if (cmd->dquote)
				cmd->dquote = 0;
			else
				cmd->dquote = 1;
			if (mode)
				src = char_remover(src, i);
		}
		else if (src[i] == 39 && !cmd->dquote)
		{
			if (cmd->squote)
				cmd->squote = 0;
			else
				cmd->squote = 1;
			if (mode)
				src = char_remover(src, i);
		}
	}
	return (src);
}

char	*char_remover(char *src, int i)
{
	char	*temp;
	char	*dup;

	if (!i)
	{
		temp = ft_strdup(&src[i + 1]);
	}
	else
	{
		dup = ft_strndup(src, i);
		temp = ft_strjoin(dup, &src[i + 1]);
		free(dup);
	}
	free(src);
	return (temp);
}
