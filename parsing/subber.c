/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:57:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/23 10:17:38 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*substitute(char *src, int i, int j, t_env *env)
{
	char	*temp;
	char	*dup;
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

int	searcher(char *str, int i, int *j)
{
	*j = i + 1;
	search_dquote(str, i, j);
	if (*j == i + 1)
		return (1);
	return (0);
}

void	search_and_sub(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	int		t;
	t_pars	*lst;

	cmd->squote = 0;
	cmd->dquote = 0;
	lst = cmd->parsed;
	t = 0;
	while (lst)
	{
		j = 0;
		i = -1;
		while (lst->value[++i])
		{
			search_squote(cmd, &lst->value, &i);
			if (lst->value[i] == '$' && lst->value[i + 1]
				&& lst->value[i + 1] != '?' && lst->value[i + 1] != ' ')
			{
				if (searcher(lst->value, i, &j))
					break ;
				else if (presubber(&lst->value, &i, j, env))
					continue ;
			}
		}
		lst = retokenize(cmd, &lst, &t);
	}
}
