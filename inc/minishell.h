#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
#include <dirent.h>

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
	int		exit_status;
	int		fd_stdin;
	int		fd_stdout;
	int		fd_out;
	int		fd_in;
	int		squote;
	int		dquote;
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
void	free_tab(char **tab);
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

			/* Parsing utils */
int		is_operator(char c);
int 	is_long_operator(char c, char b);
int		is_quote(char c);
int		type_set(char *value);
char	*check_quote(t_cmd *cmd, char *src, int i, int mode);
int		is_escapable(char c);
void	search_and_escape(t_cmd *cmd);
char	*char_remover(char *src, int i);

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

void	ft_exec(t_shell *shell, t_pars **cmd_parsed);

int		ft_redirect(t_cmd *cmd, char *redirect, t_pars **cmd_parsed);
int		ft_redirect_in(t_cmd *cmd, t_pars **cmd_parsed);
void	restaure_fd(t_shell *shell);

void	print_prompt(t_shell *shell);

// void	init_pars(t_cmd *cmd, char **arg);

#endif
