/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:19:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/19 12:40:57 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_in_dir(char *cmd_path, char **path_split, int i)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	char			*temp;
	char			*path;

	pdir = opendir(path_split[i]);
	path = NULL;
	if (pdir == NULL)
		printf("Error\nCan't open directory : %s\n", path_split[i]);
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		if (ft_strcmp(pdirent->d_name, cmd_path) == 0)
		{
			path = path_split[i];
			temp = ft_strjoin(path, "/");
			path = ft_strjoin(temp, pdirent->d_name);
			if (temp)
				free(temp);
			break ;
		}
		pdirent = readdir(pdir);
	}
	closedir(pdir);
	return (path);
}

char	*search_path(t_env *env_path, char *cmd_path)
{
	char			**path_split;
	int				i;
	char			*path;

	if (env_path == NULL)
		return (NULL);
	i = -1;
	path_split = ft_split(env_path->value, ':');
	path = NULL;
	while (path_split[++i])
	{
		path = search_in_dir(cmd_path, path_split, i);
		if (path != NULL)
			break ;
	}
	free_tab(path_split);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd_path, 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	return (path);
}

char	**fill_envp(t_env *env)
{
	char	**envp;
	int		i;
	char	*temp;

	envp = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
	i = 0;
	temp = NULL;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		envp[i++] = ft_strjoin(temp, env->value);
		if (temp)
			free(temp);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**fill_arg(t_pars **cmd_parsed)
{
	t_pars	*temp;
	int		size;
	char	**args;
	int		i;

	temp = (*cmd_parsed);
	size = 0;
	i = 0;
	while (temp && (temp->type == 1 || temp->type == 2 || temp->type == 5))
	{
		size++;
		temp = temp->next;
	}
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		exit(0);// Appeler une fonction d'erreur
	while ((*cmd_parsed) && ((*cmd_parsed)->type == 1
			|| (*cmd_parsed)->type == 2 || (*cmd_parsed)->type == 5))
	{
		args[i++] = ft_strdup((*cmd_parsed)->value);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	args[i] = NULL;
	return (args);
}

void	free_exec_arg(char **path, char ***args, char ***envp, int is_executbl)
{
	if (*path && !is_executbl)
		free(*path);
	if (*args)
		free_tab(*args);
	if (*envp)
		free_tab(*envp);
}

void	fork_exec(t_shell *shell, char *path, char **args, char **envp)
{
	errno = 0;
	unset_term(shell);
	signal(SIGQUIT, &f_sigquit);
	signal(SIGINT, &f_sigkill);
	g_pids.spid = fork();
	if (g_pids.spid == -1)
		print_error(errno);
	if (g_pids.spid == 0)
	{
		signal(SIGINT, f_sigkill);
		signal(SIGQUIT, f_sigquit);
		if (execve(path, args, envp) == -1)
			print_error(errno);
		exit(0);
	}
	else
	{
		signal(SIGINT, p_sigkill);
		signal(SIGQUIT, p_sigquit);
		if (wait(NULL) == -1)
			printf("Error with Wait\n");
	}
}

void	ft_exec(t_shell *shell, t_pars **cmd_parsed, int is_executable)
{
	char	*path;
	char	**args;
	char	**envp;

	if (is_executable)
		path = (*cmd_parsed)->value;
	else
		path = search_path(srch_and_return_env_var(shell->env, "PATH"), \
			(*cmd_parsed)->value);
	if (path == NULL)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		return ;
	}
	args = fill_arg(cmd_parsed);
	envp = fill_envp(shell->env);
	fork_exec(shell, path, args, envp);
	free_exec_arg(&path, &args, &envp, is_executable);
}
