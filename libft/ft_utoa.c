/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 11:01:22 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:43:10 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nbrlen(unsigned long long nb)
{
	unsigned int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_utoa(unsigned int n)
{
	unsigned int		size;
	char				*nbr;
	unsigned long long	nb;

	size = ft_nbrlen(n);
	nbr = ft_calloc(size + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	nb = n;
	size--;
	if (nb == 0)
		nbr[size] = 48;
	while (nb != 0)
	{
		nbr[size] = nb % 10 + 48;
		nb /= 10;
		size--;
	}
	return (nbr);
}
