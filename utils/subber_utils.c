/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:00:49 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/08 12:57:45 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*sub_empty(char *src, int i, int j)
{
	char	*dup;
	char	*temp;

	if (!i)
		temp = ft_strdup(&src[j]);
	else
	{
		dup = ft_strndup(src, i);
		temp = ft_strjoin(dup, &src[j - 1]);
		free (dup);
	}
	return (temp);
}