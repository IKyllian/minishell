/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:43:11 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/15 15:49:20 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dbl_array_print(char **dbl_array)
{
	int	i;

	i = 0;
	printf("##### LOG #####\n");
	while (dbl_array[i])
	{
		printf("%s\n", dbl_array[i]);
		i++;
	}
	printf("###############\n");
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
	char **new;
	int	i;

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
	char *new;

	new = ft_strjoin(src, elem);
	free(src);
	src = new;
}