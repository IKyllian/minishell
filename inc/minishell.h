#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "libft.h"
# include <dirent.h>

# include <term.h>

pid_t	g_pid;

typedef struct	s_pars
{
	int				type;
	char			*value;
	struct s_pars	*next;
}	t_pars;

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
	int		is_db_redir;
}	t_cmd;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_shell
{
	t_cmd	cmd;
	t_env	*env;
	struct termios	saved_term;
	struct termios	new_term;
	pid_t	pid;
	char	*line;
}	t_shell;

void	mem_check(void *ptr);

			/* Arrays */
int		dbl_array_len(char **dbl_array);
char	**dbl_array_add(char **dbl_array, char *line);
void	dbl_array_print(char **dbl_array);
void	array_joiner(char *src, char *elem);

			/* Parsing */
int		history_save(t_cmd *cmd, char *line);
int		tokenizer(t_cmd *cmd, char *line);

			/* Errors, free */
void	print_error(int errnum);
void	free_tab(char **tabl);
void	free_env_list_item(t_env *env);
void	free_env_linked_list(t_env *env);
void	free_parse_linked_list(t_pars *parse);

			/* Inits */
t_cmd	cmd_init(void);
t_shell	shell_init(char **env);

			/* Env */
t_env	*env_init(char **env_tab);
int		srch_and_rplce_env_var(t_env *env, char *to_search, char *new_value);
void	srch_and_dlt_env_var(t_env *env, char *to_search);
void	srch_and_dislay_env_var(t_env *env, char *to_search, int fd);
t_env	*srch_and_return_env_var(t_env *env, char *to_search);
int		quoting(t_cmd *cmd, char *line);

			/* Builtins */
int		ft_echo(t_shell *shell, t_pars **cmd_parsed);
int		ft_pwd(t_cmd *cmd, t_pars **cmd_parsed);
int		ft_cd(t_shell *shell, t_pars **cmd_parsed);
int		ft_export(t_shell *shell, t_pars **cmd_parded);
int		ft_unset(t_shell *shell, t_pars **cmd_parsed);
int		ft_env(t_shell *shell, t_pars **cmd_parsed);
int		ft_exit(t_shell *shell, t_pars **cmd_parsed);

			/* Signals */
void	set_term(t_shell *shell);
void	unset_term(t_shell *shell);
void	f_sigkill(int sig);
void	f_sigquit(int sig);
void	m_sigkill(int sig);

			/* Parsing utils */
int		is_operator(char c);
int 	is_long_operator(char c, char b);
int		is_quote(char c);
int		type_set(char *value);
char	*check_quote(t_cmd *cmd, char *src, int i, int mode);
void	search_and_sub(t_cmd *cmd, t_env *env);
int		search_and_escape(t_cmd *cmd);
char	*char_remover(char *src, int i);

			/* Tokenizer utils */
void	long_operator(t_cmd *cmd, int *i, int *j, int *t);
void	short_operator(t_cmd *cmd, int *i, int *j, int *t);
void	operator(t_cmd *cmd, int *i, int *j, int *t);
void	endofline(t_cmd *cmd, int *i, int *j, int *t);
void	space(t_cmd *cmd, int *i, int *j, int *t);

			/* Subber utils */
char	*sub_empty(char *src, int i, int j);
char	*sub_found(char *src, char *env_rslt, int i, int j);
void	search_squote(char *src, int *i);
void	search_dquote(char *src, int i, int *j);
int		presubber(char **src, int *i, int j, t_env *env);
char	*substitute(char *src, int i, int j, t_env *env);

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
void	lstput_pars(t_pars *lst);
void	lstclear_pars(t_pars **lst);
int		lstsize_pars(t_pars *lst);
t_pars	*lstnew_pars(char *value);
t_pars	*lstlast_pars(t_pars *lst);
void	lstaddback_pars(t_pars **alst, t_pars *new);

			/* Exec / Pipe */
void	ft_exec(t_shell *shell, t_pars **cmd_parsed);
int		check_cmd_arg(t_shell *shell, t_pars **parsed);
void	exec_pipe(t_shell *shell, t_pars **parsed, int nb_pipe);
int		check_pipe(t_pars **parsed, t_shell *shell);

			/* Redirect */
int		ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed);
int		ft_redirect_in(t_cmd *cmd, t_pars **cmd_parsed);
void	restore_fd(t_shell *shell);
// int		ft_heredoc(t_shell *shell, t_pars **cmd_parsed, t_pars *exit_word);
int	ft_heredoc(t_shell *shell, t_pars **cmd_parsed, char **exit_words, int size);

int		check_redirect(t_shell *shell, t_pars **parsed);
// void	init_pars(t_cmd *cmd, char **arg);

#endif
