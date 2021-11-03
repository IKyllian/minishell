/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:08:11 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/03 08:05:49 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pather(t_shell *shell)
{
	char	*path;

	path = malloc(sizeof(char) * 2);
	mem_check(shell, path);
	path[0] = '~';
	path[1] = '\0';
	return (path);
}
