/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:00:49 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/12 13:06:12 by ctaleb           ###   ########lyon.fr   */
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

char	*sub_found(char *src, char *env_rslt, int i, int j)
{
	char	*dup;
	char	*temp;

	if (!i)
	{
		temp = ft_strjoin(env_rslt, &src[j]);
	}
	else
	{
		dup = ft_strndup(src, i);
		temp = ft_strjoin(dup, env_rslt);
		free(dup);
		dup = temp;
		temp = ft_strjoin(dup, &src[j]);
		free(dup);
	}
	return (temp);
}

void	search_squote(char *src, int *i)
{
	if (src[*i] == '\'')
	{
		while (src[*i])
		{
			*i += 1;
			if (src[*i] && src[*i] == '\'')
			{
				i += 1;
				break ;
			}
		}
	}
}

void	search_dquote(char *src, int i, int *j)
{
	while (src[*j] && src[*j] != ' ' && src[*j] != '"')
	{
		if (*j == i + 1 && (ft_isalpha(src[*j]) || src[*j] == '_'))
			*j += 1;
		else if (ft_isalnum(src[*j]) || src[*j] == '_')
			*j += 1;
		else
			break ;
	}
}

int		presubber(char **src, int *i, int j, t_env *env)
{
	*src = substitute(*src, *i, j, env);
	*i = -1;
	return (1);
}