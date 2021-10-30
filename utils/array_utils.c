/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:43:11 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/30 08:42:37 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dbl_array_clear(char **dbl_array)
{
	int	i;

	i = 0;
	if (!dbl_array)
		return ;
	while (dbl_array[i])
	{
		free(dbl_array[i]);
		i++;
	}
	free(dbl_array);
}

int	dbl_array_len(char **dbl_array)
{
	int	i;

	i = 0;
	while (dbl_array[i])
		i++;
	return (i);
}

char	**dbl_array_add(char **dbl_array, char *line)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), dbl_array_len(dbl_array) + 2);
	mem_check(new);
	i = 0;
	while (dbl_array[i])
	{
		new[i] = dbl_array[i];
		i++;
	}
	new[i] = ft_strdup(line);
	free (dbl_array);
	return (new);
}

void	array_joiner(char *src, char *elem)
{
	char	*new;

	new = ft_strjoin(src, elem);
	free(src);
	src = new;
}
