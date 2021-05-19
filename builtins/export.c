/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:29:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/30 16:02:14 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*cpy_env_list(t_env *env)
{
	t_env	*cpy_env;

	cpy_env = NULL;
	while (env)
	{
		ft_lstadd_back_env(&cpy_env, ft_lstnew_env(ft_strdup(env->name),\
			ft_strdup(env->value)));
		env = env->next;
	}
	return (cpy_env);
}

void	print_env_line(t_shell *shell)
{
	ft_putstr_fd("declare -x ", shell->cmd.fd);
	ft_putstr_fd(shell->env->name, shell->cmd.fd);
	if (shell->env->value != NULL)
	{
		ft_putstr_fd("=\"", shell->cmd.fd);
		ft_putstr_fd(shell->env->value, shell->cmd.fd);
		ft_putchar_fd('\"', shell->cmd.fd);
	}
	ft_putchar_fd('\n', shell->cmd.fd);
}

void	sort_env(t_env *env_cpy, t_env *first) // First = Pointeur sur le premier element de la liste
{
	char *name_temp;
	char *value_temp;
	int is_sort;

	is_sort = 0;
	while (!is_sort)
	{
		is_sort = 1;
		env_cpy = first;
		while (env_cpy)
		{
			if (env_cpy->next && ft_strcmp(env_cpy->name, env_cpy->next->name) > 0)
			{
				name_temp = env_cpy->name;
				value_temp = env_cpy->value;
				env_cpy->name = env_cpy->next->name;
				env_cpy->value = env_cpy->next->value;
				env_cpy->next->name = name_temp;
				env_cpy->next->value = value_temp;
				is_sort = 0;
			}
			env_cpy = env_cpy->next;
		}
	}
}

void	sort_and_print_env(t_shell *shell)
{
	t_env *env_cpy;
	t_env *env;

	env_cpy = cpy_env_list(shell->env);
	env = env_cpy;
	sort_env(env_cpy, env);
	while (env)
	{
		print_env_line(shell);
		env = env->next;
	}
	free_linked_list(env_cpy);
}

// exit status = 0 if no error, >0 if an error occured
int	ft_export(t_shell *shell)//, char **arg)
{
	// if (line[1] == NULL) // Si aucun argument print juste les variables env
		sort_and_print_env(shell);
	// else // Sinon add une variable dans la liste
	// {
			//Check si la variable existe deja
			//Si oui modifie la valeur de la variable
			// if (!srch_and_rplce_env_var(env, arg[1], arg[2]))
			// 	ft_lstadd_back_env(env, ft_lstnew_env(arg[1], arg[2]));
			//Sinon ajoute la variable dans la liste env
	// 			
	// }
	return (0);	
}
