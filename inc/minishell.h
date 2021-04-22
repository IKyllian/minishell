#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct s_env
{
	char **tab_env;
	int	old_path_index;
}				t_env;

void	print_error(int errnum);
void	free_tab(char **tab);

t_env	env_init(char **env_tab);
void	add_env_var(t_env *env, char *name, char *value);
void	change_env_var(t_env *env, char *name, char *value);

int		ft_echo(char *str);
int		ft_pwd(void);
int		ft_cd(const char *path, t_env *env);
int		ft_export(t_env *env);

#endif