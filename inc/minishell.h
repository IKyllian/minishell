#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

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
int		history_save(t_cmd *cmd);
int		tokenizer(t_cmd *cmd);

			/* Errors, free */
void	print_error(int errnum);
void	free_tab(char **tab);
void	free_list_item(t_env *env);
void	free_linked_list(t_env *env);

			/* Inits */
t_cmd	cmd_init(void);
t_shell	shell_init(char **env);

			/* Env */
t_env	*env_init(char **env_tab);
int		srch_and_rplce_env_var(t_env *env, char *to_search, char *new_value);
void	srch_and_dlt_env_var(t_env *env, char *to_search);
void	srch_and_dislay_env_var(t_env *env, char *to_search);
int		quoting(t_cmd *cmd, char *line);

			/* Builtins */
int		ft_echo(char *str);
int		ft_pwd(void);
int		ft_cd(const char *path, t_env *env);
int		ft_export(t_env *env);
int		ft_unset(t_env *env, char **arg);
int		ft_env(t_env *env);
int		ft_exit(t_env *env);

			/* List utils */
int		ft_lstsize_env(t_env *lst);
t_env	*ft_lstnew_env(char *name, char *value);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);

void	lstput_pars(t_pars *lst);
void	lstclear_pars(t_pars **lst);
int		lstsize_pars(t_pars *lst);
t_pars	*lstnew_pars(char *value);
t_pars	*lstlast_pars(t_pars *lst);
void	lstaddback_pars(t_pars **alst, t_pars *new);

#endif