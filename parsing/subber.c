/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:57:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/11 13:41:27 by ctaleb           ###   ########lyon.fr   */
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
		temp = sub_empty(src, i, j);
	else
		temp = sub_found(src, env_rslt->value, i, j);
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
		i = -1;
		while (lst->value[++i])
		{
			search_squote(lst->value, &i);
			if (lst->value[i] == '$' && lst->value[i + 1]
					&& lst->value[i + 1] != '?' && lst->value[i + 1] != ' ')
			{
				j = i + 1;
				search_dquote(lst->value, i, &j);
				if (j == i + 1)
					break ;
				else if (presubber(&lst->value, &i, j, env))
					continue ;
			}
		}
		lst = lst->next;
	}
}