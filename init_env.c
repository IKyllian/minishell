/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:25:19 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/22 16:48:16 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	get_env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	change_env_var(t_env *env, char *name, char *value)
{
	int i;

	i = env->old_path_index;
	free(env->tab_env[i]);
	env->tab_env[i] = ft_strjoin(name, value);
}

void	add_env_var(t_env *env, char *name, char *value)
{
	char	**new_tab;
	int		i;

	i = -1;
	new_tab = malloc(sizeof(char *) * (get_env_len(env->tab_env) + 2)); // 2 = 1 nouveau element + dernier element a NULL
	if (!new_tab)
		exit(0);
	while (env->tab_env[++i])
		new_tab[i] = ft_strdup(env->tab_env[i]);
	env->old_path_index = i;
	new_tab[i++] = ft_strjoin(name, value);
	new_tab[i] = NULL;
	free_tab(env->tab_env);
	env->tab_env = new_tab;
}

t_env	env_init(char **env_tab)
{
	int		i;
	t_env	env;

	i = -1;
	env.tab_env = malloc(sizeof(char *) * (get_env_len(env_tab) + 1));
	if (!env.tab_env)
		exit(0);
	while (env_tab[++i])
		env.tab_env[i] = ft_strdup(env_tab[i]);
	env.tab_env[i] = NULL;
	env.old_path_index = -1;
	return (env);
}