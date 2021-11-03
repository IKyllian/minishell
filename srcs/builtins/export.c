/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:29:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/03 08:08:17 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_export_name(char *cmd_value, int *index, t_shell *shell)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd_value[*index] && cmd_value[*index] != '=')
		(*index)++;
	name = malloc(sizeof(char) * (*index + 1));
	mem_check(shell, name);
	while (cmd_value[i])
	{
		if ((cmd_value[i] == '=' && i != 0))
			break ;
		if (!is_valide_character(cmd_value[i], cmd_value, i, shell))
		{
			free(name);
			return (NULL);
		}
		if ((cmd_value[i] == '+'
				&& cmd_value[i + 1] && cmd_value[i + 1] == '='))
			break ;
		name[i] = cmd_value[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_export_value(char *cmd_value, int *index, t_shell *shell)
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
			mem_check(shell, value);
			value[0] = '\0';
		}
		else
		{
			value = malloc(sizeof(char) * ((size - *index) + 1));
			mem_check(shell, value);
			size = 0;
			while (cmd_value[*index])
				value[size++] = cmd_value[(*index)++];
			value[size] = '\0';
		}
		return (value);
	}
}

void	exec_error(t_shell *shell, t_pars **cmd_parsed, int *has_error)
{
	ft_putstr_fd("minishell: export: \'", shell->cmd.fd_out);
	ft_putstr_fd((*cmd_parsed)->value, shell->cmd.fd_out);
	ft_putstr_fd("\': not a valid identifier\n", shell->cmd.fd_out);
	*has_error = 1;
}

int	exec_export(t_pars **cmd_parsed, t_shell *shell, char **name, int *index)
{
	char	*value;

	value = get_export_value((*cmd_parsed)->value, index, shell);
	if (!value && *index > 0 && (*cmd_parsed)->value[*index - 1] != '='
		&& srch_and_return_env_var(shell->env, *name))
	{
		free(*name);
		(*cmd_parsed) = (*cmd_parsed)->next;
		return (1);
	}
	else if (!srch_and_rplce_env_var(shell->env, *name, value, \
		shell->cmd.mode_export))
		ft_lstadd_back_env(&shell->env, ft_lstnew_env(*name, value, shell));
	else
		free(*name);
	return (0);
}

int	ft_export(t_shell *shell, t_pars **cmd_parsed)
{
	char	*name;
	int		index;
	int		has_error;

	name = NULL;
	index = 0;
	has_error = 0;
	if ((*cmd_parsed)->next == NULL || (*cmd_parsed)->next->type != 2)
	{
		sort_and_print_env(shell);
		(*cmd_parsed) = (*cmd_parsed)->next;
		return (has_error);
	}
	(*cmd_parsed) = (*cmd_parsed)->next;
	while ((*cmd_parsed) && (*cmd_parsed)->type == 2)
	{
		index = 0;
		name = get_export_name((*cmd_parsed)->value, &index, shell);
		if (name == NULL)
			exec_error(shell, cmd_parsed, &has_error);
		if (name && exec_export(cmd_parsed, shell, &name, &index) == 1)
			continue ;
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	return (has_error);
}
