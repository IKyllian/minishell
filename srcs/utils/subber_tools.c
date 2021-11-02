/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:29:16 by ctaleb            #+#    #+#             */
/*   Updated: 2021/11/02 13:10:05 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_exit_status(t_shell *shell, char **str, int *i)
{
	char	*dup;
	char	*temp;
	char	*env;

	if ((*str)[*i] == '$' && (*str)[*i + 1] && (*str)[*i + 1] == '?')
	{
		env = ft_itoa(shell->cmd.exit_status);
		dup = ft_strndup(*str, *i);
		temp = ft_strjoin(dup, env);
		free(env);
		free(dup);
		dup = ft_strdup(&(*str)[*i + 2]);
		free(*str);
		*str = ft_strjoin(temp, dup);
		free(dup);
		free(temp);
		// printf("%s\n", *str);
	}
}
