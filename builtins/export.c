/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:29:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/23 16:33:16 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	sort_env(t_env *env)
// {
// 	int size;
// 	t_env *first;

// 	size = ft_lstsize_env(env);
// 	while (env && size)
	
// }

void	print_env_tab(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

int	ft_export(t_env *env)//, char **line)
{
	// if (line[1] == NULL) // Si aucun argument print juste les variables env
		print_env_tab(env);
	// else // Sinon add une variable dans la liste
	// {
	// 		ft_lstadd_back_env(env, ft_lstnew_env(name, value));
	// }
	return (0);	
}