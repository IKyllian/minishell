/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subber.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 08:57:44 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/24 16:26:14 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*avoider(char *str)
{
	char	*env;
	char	*temp;
	int		i;

	i = 0;
	env = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			env = ft_strndup(str, i);
			temp = ft_strjoin(env, "\\");
			free(env);
			env = ft_strjoin(temp, &str[i]);
			free(temp);
		}
		i++;
	}
	if (!env)
		env = ft_strdup(str);
	return (env);
}

char	*substitute(char *src, int i, int j, t_shell *shell)
{
	char	*temp;
	char	*dup;
	char	*env;
	t_env	*env_rslt;

	dup = ft_strndup(&src[i + 1], j - i - 1);
	env_rslt = srch_and_return_env_var(shell->env, dup);
	free (dup);
	if (!env_rslt)
		temp = sub_empty(src, i, j);
	else
	{
		env = avoider(env_rslt->value);
		temp = sub_found(src, env, i, j);
		free(env);
	}
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

void	search_and_sub(t_shell *shell)
{
	int		i;
	int		j;
	t_pars	*lst;

	lst = shell->cmd.parsed;
	shell->token = 0;
	while (lst)
	{
		j = 0;
		i = -1;
		while (lst->value[++i])
		{
			search_squote(lst->value, &i);
			if (lst->value[i] == '$' && lst->value[i + 1]
				&& lst->value[i + 1] != '?' && lst->value[i + 1] != ' ')
			{
				if (searcher(lst->value, i, &j))
					break ;
				else if (presubber(&lst->value, &i, j, shell))
					continue ;
			}
		}
		lst = retokenize(&shell->cmd, &lst, &shell->token);
	}
}
