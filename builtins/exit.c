#include "../inc/minishell.h"

// exit [n] exit status = if n specified exit status is n except if n is not an unsigned decimal integer
// or greater than 255, else the value of exit status is the value of the last command 
// int	ft_exit(t_env *env)
// {
// 	return (0);
// }