/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:35:08 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/12 13:37:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	free_env_list_item(t_env *env)
{
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	if (env)
		free(env);
}

void	free_env_linked_list(t_env *env)
{
	t_env *next;

	next = NULL;
	while (env)
	{
		if (env->next)
			next = env->next;
		else
			next = NULL;
		free_env_list_item(env);
		env = next;
	}
}

void	free_parse_linked_list(t_pars *parse)
{
	t_pars *next;

	next = NULL;
	while (parse)
	{
		if (parse->next)
			next = parse->next;
		else
			next = NULL;
		if (parse->value)
			free(parse->value);
		if (parse)
			free(parse);
		parse = next;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	print_error(int errnum)
{
	ft_putstr_fd(strerror(errnum), 1);
	ft_putchar_fd('\n', 1);
	errno = 0;
}