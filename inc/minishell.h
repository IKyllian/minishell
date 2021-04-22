#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct s_cmd {
	char	**history;
	char	**parsed;
}	t_cmd;

t_cmd	cmd_init(void);

void	mem_check(void *ptr);

int		dbl_array_len(char **dbl_array);
char	**dbl_array_add(char **dbl_array, char *line);
void	dbl_array_print(char **dbl_array);

int		history_save(t_cmd *cmd, char *line);


int		ft_echo(char *str);
int		ft_pwd(void);
int		ft_cd(const char *path);

#endif