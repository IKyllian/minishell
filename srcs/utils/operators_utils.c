/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:29:01 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 13:09:37 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_long_operator(char c, char b)
{
	if ((b == '<' && c == b) || (b == '>' && c == b))
		return (1);
	return (0);
}

int	type_set(char *value)
{
	int		len;

	len = ft_strlen(value);
	if (len == 1 && value[0] == '|')
		return (3);
	else if (len == 1 && (value[0] == '<' || value[0] == '>'))
		return (4);
	else if (len == 2 && value[0] == '>' && value[1] == '>')
		return (4);
	else if (len == 2 && value[0] == '<' && value[1] == '<')
		return (4);
	else if (value[0] && value [1]
		&& (((value[0] == '.' || value[0] == '~') && value[1] == '/')
			|| value[0] == '/'))
		return (5);
	else
		return (2);
}
