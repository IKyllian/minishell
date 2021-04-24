/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:25:19 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/23 16:45:39 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	srch_and_dlt_env_var(t_env *env, char *to_search)
{
	int		i;
	t_env	*prev;

	prev = NULL;
	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0')
			{
				if (prev && !env->next)
					prev->next = NULL;
				else if (prev && env->next)
					prev->next = env->next;
				free_list_item(env);
				break ;
			}
			i++;
		}
		prev = env;
		env = env->next;
	}
}

void	srch_and_rplce_env_var(t_env *env, char *to_search, char *new_value)
{
	int i;

	while (env)
	{
		i = 0;
		while (env->name[i] && to_search[i] && env->name[i] == to_search[i])
		{
			if (to_search[i + 1] == '\0')
			{
				free(env->value);
				env->value = new_value;
				break ;
			}
			i++;
		}
		env = env->next;
	}
}

void	get_env_var(char *line, char **lst_name, char **lst_value)
{
	int		i; // Sert a connaitre la len de la value (valeur de la variable)
	int		j; // Sert d'index pour remplir name et value
	int		len; // Sert, en premier à connaitre la taille de name (nom de la varaible), puis à connaitre la len totale de line
	char	*name;
	char	*value;
	
	i = 0;
	j = -1;
	len = 0;
	while (line[len] && line[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	while (line[++j] && line[j] != '=')
		name[j] = line[j];
	name[j] = '\0';
	j = 0;
	while (line[++len])
		i++;
	value = malloc(sizeof(char) * (i + 1));
	while (line[len - i] && i >= 0)
		value[j++] = line[len - i--];
	value[j] = '\0';
	*lst_name = name;
	*lst_value = value;
}

t_env	*env_init(char **env_tab)
{
	int	i;
	t_env *env;
	char *name;
	char *value;

	i = -1;
	env = NULL;
	while (env_tab[++i])
	{
		get_env_var(env_tab[i], &name, &value);
		ft_lstadd_back_env(&env, ft_lstnew_env(name, value));
	}
	return (env);
}