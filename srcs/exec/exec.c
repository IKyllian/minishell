/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:19:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/10/30 08:42:22 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_in_dir(char *cmd_path, char **path_split, int i, int *has_right)
{
	DIR				*pdir;
	struct dirent	*pdirent;
	char			*path;

	pdir = opendir(path_split[i]);
	path = NULL;
	if (pdir == NULL)
	{
		ft_putstr_fd("Error\nCan't open directory : ", 2);
		ft_putstr_fd(path_split[i], 2);
		ft_putstr_fd("\n", 2);
	}
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		if (ft_strcmp(pdirent->d_name, cmd_path) == 0)
		{
			join_path(path_split, i, pdirent, &path);
			if (check_access(&path, has_right) == 1)
				break ;
		}
		pdirent = readdir(pdir);
	}
	closedir(pdir);
	return (path);
}

char	*search_path(t_env *env_path, char *cmd_path, int fd)
{
	char	**path_split;
	int		i;
	char	*path;
	int		has_right;		

	if (env_path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	i = -1;
	has_right = 1;
	path_split = ft_split(env_path->value, ':');
	path = NULL;
	while (path_split[++i])
	{
		path = search_in_dir(cmd_path, path_split, i, &has_right);
		if (path != NULL)
			break ;
	}
	dbl_array_clear(path_split);
	path_error(path, has_right, fd, cmd_path);
	return (path);
}

char	**fill_arg(t_pars **cmd_parsed, t_shell *shell)
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
		ft_exit(shell, cmd_parsed);
	while ((*cmd_parsed) && ((*cmd_parsed)->type == 1
			|| (*cmd_parsed)->type == 2 || (*cmd_parsed)->type == 5))
	{
		args[i++] = ft_strdup((*cmd_parsed)->value);
		(*cmd_parsed) = (*cmd_parsed)->next;
	}
	args[i] = NULL;
	return (args);
}

void	fork_exec(t_shell *shell, char *path, char **args, char **envp)
{
	int	status;

	errno = 0;
	unset_term(shell);
	shell->cmd.pids->spid = fork();
	if (shell->cmd.pids->spid == -1)
		print_error(errno);
	if (shell->cmd.pids->spid == 0)
	{
		signal(SIGINT, f_sigkill);
		signal(SIGQUIT, f_sigquit);
		if (execve(path, args, envp) == -1)
		{
			print_error(errno);
			exit(1);
		}
		exit(0);
	}
	signal(SIGINT, p_sigkill);
	signal(SIGQUIT, p_sigquit);
	if (wait(&status) == -1)
		ft_putstr_fd("Error with Wait\n", 2);
	shell->cmd.exit_status = set_exit_status(status);
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
			(*cmd_parsed)->value, 2);
	if (path == NULL)
	{
		(*cmd_parsed) = (*cmd_parsed)->next;
		shell->cmd.exit_status = 127;
		return ;
	}
	else
	{
		args = fill_arg(cmd_parsed, shell);
		envp = fill_envp(shell->env);
		fork_exec(shell, path, args, envp);
		if (shell->cmd.exit_status > 0 && is_executable)
			shell->cmd.exit_status = 127;
	}
	free_exec_arg(&path, &args, &envp, is_executable);
}
