#include "../inc/minishell.h"

int	num_is_valid(char *str)
{
	int	i;
	int nb;
	int is_neg;

	i = -1;
	nb = 0;
	is_neg = 0;
	while (str[++i])
	{
		if (i == 0 && str[i] == '-')
			is_neg = 1;
		if (!(str[i] >= 48 && str[i] <= 57))
			return (-1);
		nb = (nb * 10) + (str[i] - 48);
	}
	if (is_neg || nb > 255)
		return (-1);
	return (nb);
}
// exit [n] exit status = if n specified exit status is n except if n is not an unsigned decimal integer
// or greater than 255, else the value of exit status is the value of the last command 
// int	ft_exit(t_env *env, char **arg)
// {
	// int nb;
	// if (arg[1])
	// {
	// 	nb = check_num(arg[1]);
	// 	if (nb =! -1)
	// 		//set exit status with the value of nb
	// }
	// free_linked_list(env);
// 	return (0);
// }