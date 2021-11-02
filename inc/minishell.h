/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 08:52:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/11/02 14:47:12 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <dirent.h>

# include <term.h>

int				g_heredoc;

typedef struct s_pars
{
	int				type;
	char			*value;
	struct s_pars	*next;
}	t_pars;

typedef struct s_pid
{
	pid_t	pid;
	int		is_heredoc;
}	t_pid;

typedef struct s_pids
{
	t_pid	*pid;
	pid_t	spid;
	int		count;
}	t_pids;

typedef struct s_redir
{
	int		type;
	char	*value;
	int		pipe_index;
}	t_redir;

typedef struct s_cmd
{
	char	**history;
	char	*line;
	t_pars	*parsed;
	char	*prompt;
	int		exit_status;
	int		fd_stdin;
	int		fd_stdout;
	int		fd_out;
	int		fd_in;
	int		squote;
	int		dquote;
	int		is_heredoc;
	int		hd_has_error;
	int		i_pids;
	t_redir	*redir;
	int		i_redir;
	int		recount;
	int		is_pipe;
	int		index_pipe;
	int		set_old_to_null;
	int		nbr_pipe;
	int		mode_export;
	int		pipe_fd;
	t_pids	*pids;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_cmd			cmd;
	t_env			*env;
	struct termios	saved_term;
	struct termios	new_term;
	char			*line;
	int				token;
}	t_shell;

			/* Memory */
void	free_all(t_shell *shell);
void	mem_check(t_shell *shell, void *ptr);

			/* Arrays */
int		dbl_array_len(char **dbl_array);
char	**dbl_array_add(char **dbl_array, char *line, t_shell *shell);
void	dbl_array_clear(char **dbl_array);
void	array_joiner(char *src, char *elem);

			/* Parsing */
int		history_save(t_cmd *cmd, char *line, t_shell *shell);
int		tokenizer(t_cmd *cmd, char *line, t_shell *shell);
int		redirect(t_cmd *cmd);

			/* Errors, free */
void	print_error(int errnum);
void	free_tab(char **tabl);
void	free_env_list_item(t_env *env);
void	free_parse_linked_list(t_pars *parse);
void	free_redir(t_shell *shell);

			/* Inits */
t_cmd	cmd_init(void);
t_shell	shell_init(char **env);

			/* Env */
t_env	*env_init(char **env_tab, t_shell *shell);
int		srch_and_rplce_env_var(t_env *env, char *to_srch, char *new, int mode);
void	srch_and_dlt_env_var(t_env **env, char *to_search);
void	srch_and_dislay_env_var(t_env *env, char *to_search, int fd);
t_env	*srch_and_return_env_var(t_env *env, char *to_search);
int		quoting(t_cmd *cmd, char *line);
void	check_first_node(t_env	*first, t_env **env, t_env	*prev);
void	replace_env_var(t_env *env, char *new_val, int mode);

			/* Builtins */
int		ft_echo(t_shell *shell, t_pars **cmd_parsed);
int		ft_pwd(t_cmd *cmd, t_pars **cmd_parsed);
int		ft_cd(t_shell *shell, t_pars **cmd_parsed);
int		ft_export(t_shell *shell, t_pars **cmd_parded);
int		ft_unset(t_shell *shell, t_pars **cmd_parsed);
int		ft_env(t_shell *shell, t_pars **cmd_parsed);
void	ft_exit(t_shell *shell, t_pars **cmd_parsed);
void	ft_exit_pipe(t_shell *shell, t_pars **cmd_parsed);
int		get_exit_nb(t_shell *shell, t_pars **cmd_parsed);
int		num_is_valid(char *str);
int		get_nb(char *str, int i, int *nb);
int		exit_nbr_caster(int nb);
int		set_exit_status(int status);
int		is_valide_character(char c, char *cmd_value, int indx, t_shell *shell);
void	sort_and_print_env(t_shell *shell);
int		end_cd(t_shell *shell, t_pars **cmd_parsed);

			/* Signals */
void	sighandler(int sig);
void	set_term(t_shell *shell);
void	unset_term(t_shell *shell);
void	ign_sigkill(int sig);
void	ign_sigquit(int sig);
void	p_sigkill(int sig);
void	p_sigquit(int sig);
void	f_sigkill(int sig);
void	f_sigquit(int sig);
void	m_sigkill(int sig);
int		set_exit_status(int status);

			/* Parsing utils */
int		validator(t_shell *shell);
int		is_operator(char c);
int		is_long_operator(char c, char b);
int		is_quote(char c);
int		type_set(char *value);
char	*check_quote(t_cmd *cmd, char *src, int i, int mode);
void	search_and_sub(t_shell *shell);
int		search_and_escape(t_cmd *cmd);
char	*char_remover(char *src, int i);

			/* Tokenizer utils */
void	long_operator(t_shell *shell, int *i, int *j, int *t);
void	short_operator(t_shell *shell, int *i, int *j, int *t);
void	operator(t_shell *shell, int *i, int *j, int *t);
void	endofline(t_shell *shell, int *i, int *j, int *t);
void	space(t_shell *shell, int *i, int *j, int *t);

			/* Subber utils */
char	*sub_empty(char *src, int i, int j);
char	*sub_found(char *src, char *env_rslt, int i, int j);
void	search_squote(char *src, int *i);
void	search_dquote(char *src, int i, int *j);
int		presubber(char **src, int *i, int j, t_shell *shell);
char	*substitute(char *src, int i, int j, t_shell *shell);
void	sub_exit_status(t_shell *shell, char **str, int *i);

			/* Retokenize utils */
t_pars	*retokenize(t_shell *shell, t_cmd *cmd, t_pars **token, int *t);

			/* Prompt */
char	*pather(void);
void	check_cmd(t_shell *shell);
void	set_prompt(t_shell *shell, char **prompt);
int		prompt(t_shell *shell);

			/* List utils (t_env) */
int		ft_lstsize_env(t_env *lst);
t_env	*ft_lstnew_env(char *name, char *value);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);

			/* List utils (t_pars) */
t_pars	*lst_replace_start(t_cmd *cmd, t_pars *new_tokens, int *t);
t_pars	*lst_replace(t_pars *lst, t_pars *new_tokens, int *t);
void	lstdel_beg_pars(t_pars **lst);
void	lstdel_other_pars(t_pars **lst, int d);
void	lstclear_pars(t_pars **lst);
int		lstsize_pars(t_pars *lst);
t_pars	*lstnew_pars(char *value, t_shell *shell);
t_pars	*lstlast_pars(t_pars *lst);
void	lstaddback_pars(t_pars **alst, t_pars *new);
void	lstclear_env(t_env **lst);

			/* Exec / Pipe */
void	ft_exec(t_shell *shell, t_pars **cmd_parsed, int is_executable);
int		cmd_to_exec(t_shell *shell, t_pars **parsed);
void	exec_pipe(t_shell *shell, t_pars **parsed);
int		check_pipe(t_pars **parsed, t_shell *shell);
char	*first_search(char **cmd_path, int *has_right, t_shell *shell);
void	join_exec_path(char *path_dir, struct dirent *pdirent, char **path);
void	free_exec_arg(char **path, char ***args, char ***envp, int is_executbl);
char	**fill_envp(t_env *env);
int		check_access(char **path, int *has_right);
int		path_error(char *path, int has_right, int fd, char *cmd_path);
int		check_executable(t_shell *shell, t_pars **cmd_parsed, char **path);
char	*error_path_env(char **cmd_path);
char	*error_pdir(char **join_path);
void	dup_pipe(t_shell *shell, int in, int out);
void	next_cmd(t_pars **parsed);
void	exec_child(t_shell *shell, t_pars **parsed);
int		pipe_count(t_pars *parsed, t_cmd *cmd);

			/* Redirect */
int		check_redirect(t_shell *shell, t_pars **parsed, int index_cmd);
int		redirect_comparator(t_pars *lst, t_cmd *cmd, int *j, int p_i);
int		ft_redirect(t_cmd *cmd, t_redir redir);
int		ft_redirect_in(t_cmd *cmd, t_redir redir);
void	restore_cmd(t_shell *shell);
int		ft_heredoc(t_shell *shell, t_pars **cmd_parsed);
int		check_heredoc(t_shell *shell, t_pars **parsed, int ret);
void	init_heredoc(t_shell *shell, t_pars *parsed);
void	heredoc_echo(t_pars **cmd_parsed, t_pars **args, t_shell *shell);

#endif
