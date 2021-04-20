/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:43:48 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 16:28:25 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nbrlen(long long nb)
{
	unsigned int	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

static char	*ft_maxcase(void)
{
	char	*nbr;
	char	*str;
	int		i;

	nbr = ft_calloc(21, sizeof(char));
	if (!nbr)
		return (NULL);
	str = "-9223372036854775808";
	i = 0;
	while (i < 21)
	{
		nbr[i] = str[i];
		i++;
	}
	return (nbr);
}

char	*ft_ltoa(long long n)
{
	unsigned int		size;
	char				*nbr;
	long long			nb;

	if (9223372036854775808U == (unsigned long long)n)
		return (ft_maxcase());
	size = ft_nbrlen(n);
	nbr = ft_calloc(size + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		nbr[0] = '-';
		nb *= -1;
	}
	size--;
	if (nb == 0)
		nbr[size] = 48;
	while (nb != 0)
	{
		nbr[size--] = nb % 10 + 48;
		nb /= 10;
	}
	return (nbr);
}
