/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:29:01 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/13 08:31:23 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//need to prevent lone operators from doing nothing; should give a syntax error

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == ';' || c == '<' || c == '>' || c == '|'/* || c == '*'
		|| c == '&'*/)
		return (1);
	return (0);
}

int is_long_operator(char c, char b)
{
	if ((b == '<' && c == b) || (b == '>' && c == b)/* || (b == '&' && c == b)
		|| (b == '|' && c == b) */|| (b == '$' && c == '?'))
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