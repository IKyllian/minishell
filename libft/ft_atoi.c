/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:03:04 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 16:25:40 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	symbol_set(char symbol)
{
	if (symbol == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					i;
	int					sym;

	i = 0;
	sym = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sym = symbol_set(str[i++]);
	nb = 0;
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (nb > 9223372036854775807)
	{
		if (sym > 0)
			return (-1);
		else
			return (0);
	}
	return (nb * sym);
}
