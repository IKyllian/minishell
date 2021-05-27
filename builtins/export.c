/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:29:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/05/19 16:37:44 by kdelport         ###   ########lyon.fr   */
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

void	print_env_line(t_env *env, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env->name, fd);
	if (env->value != NULL)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(env->value, fd);
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
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
	t_env *first;

	env_cpy = cpy_env_list(shell->env);
	first = env_cpy;
	sort_env(env_cpy, first);
	while (first)
	{
		print_env_line(first, shell->cmd.fd_out);
		first = first->next;
	}
	free_env_linked_list(env_cpy);
}

char	*get_export_name(char *cmd_value, int *index)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd_value[*index] && cmd_value[*index] != '=')
		(*index)++;
	name = malloc(sizeof(char) * (*index + 1));
	mem_check(name);
	while (cmd_value[i] && cmd_value[i] != '=')
	{
		name[i] = cmd_value[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_export_value(char *cmd_value, int *index)
{
	int		size;
	char	*value;

	size = ft_strlen(cmd_value);
	if (cmd_value[*index] == '\0')
		return (NULL);
	else
	{
		if (cmd_value[++(*index)] == '\0')
		{
			value = malloc(sizeof(char));
			mem_check(value);
			value[0] = '\0';
		}
		else
		{
			value = malloc(sizeof(char) * ((size - *index) + 1));
			mem_check(value);
			size = 0;
			while (cmd_value[*index])
				value[size++] = cmd_value[(*index)++];
			value[size] = '\0';
		}
		return (value);
	}
}

int	ft_export(t_shell *shell, t_pars **cmd_parsed)
{
	char	*name;
	char	*value;
	int		index;

	name = NULL;
	value = NULL;
	index = 0;
	if ((*cmd_parsed)->next == NULL || (*cmd_parsed)->next->type != 2) // Si aucun argument ou que le type n'est pas un argument print juste les variables env
	{
		sort_and_print_env(shell);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	else // Sinon add une variable dans la liste
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
		{
			index = 0;
			// Check si la variable existe deja
			// Si oui modifie la valeur de la variable / Check si la prochaine liste est aussi un argument
			name = get_export_name((*cmd_parsed)->value, &index);
			value = get_export_value((*cmd_parsed)->value, &index);
			if (!srch_and_rplce_env_var(shell->env, name, value))
				ft_lstadd_back_env(&shell->env, ft_lstnew_env(name, value)); // Sinon ajoute la variable dans la liste env
			(*cmd_parsed) = (*cmd_parsed)->next;
		}
		shell->cmd.exit_status = 0;
	}
	return (0);	
}
