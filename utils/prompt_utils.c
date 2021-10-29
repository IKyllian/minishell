/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:08:11 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 16:13:20 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pather(void)
{
	char	*path;

	path = malloc(sizeof(char) * 2);
	path[0] = '~';
	path[1] = '\0';
	return (path);
}
