/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:29:01 by ctaleb            #+#    #+#             */
/*   Updated: 2021/05/03 15:28:23 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_operator(char c)
{
	if (c == ';' || c == '<' || c == '>' || c == '|' || c == '*'
		|| c == '&')
		return (1);
	else
		return (0);
}

int is_long_operator(char c, char b)
{
	if ((b == '>' && c == b) || (b == '<' && c == b) || (b == '&' && c == b)
		|| (b == '|' && c == b) || (b == '$' && c == '?'))
		return (1);
	else
		return (0);
}