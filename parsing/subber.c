/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:57:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/09/24 08:20:55 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*substitute(char *src, int i, int j, t_env *env)
{
	char 	*temp;
	char 	*dup;
	t_env	*env_rslt;

	dup = ft_strndup(&src[i + 1], j - i - 1);
	env_rslt = srch_and_return_env_var(env, dup);
	free (dup);
	if (!env_rslt)
	{
		if (!i)
			temp = ft_strdup(&src[j]);
		else
		{
			dup = ft_strndup(src, i);
			temp = ft_strjoin(dup, &src[j - 1]);
			free (dup);
		}
	}
	else
	{
		if (!i)
		{
			temp = ft_strjoin(env_rslt->value, &src[j]);
		}
		else
		{
			dup = ft_strndup(src, i);
			temp = ft_strjoin(dup, env_rslt->value);
			free(dup);
			dup = temp;
			temp = ft_strjoin(dup, &src[j]);
			free(dup);
		}
	}
	free(src);
	return (temp);
}

void	search_and_sub(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	t_pars	*lst;

	lst = cmd->parsed;
	while(lst)
	{
		j = 0;
		i = 0;
		while (lst->value[i])
		{
			if (lst->value[i] == '\'')
				break ;
			if (lst->value[i] == '$' && lst->value[i + 1]
					&& lst->value[i + 1] != '?' && lst->value[i + 1] != ' ')
			{
				j = i;
				while (lst->value[j] && lst->value[j] != ' ' && lst->value[j] != '"')
					j++;
				if (j == i + 1)
					break ;
				else
				{
					lst->value = substitute(lst->value, i, j, env);
					i = 0;
					continue ;
				}
			}
			i++;
		}
		lst = lst->next;
	}
}