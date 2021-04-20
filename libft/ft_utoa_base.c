/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 11:00:49 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:42:27 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nbrlen(unsigned long long nb, unsigned int blen)
{
	unsigned int	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= blen;
		size++;
	}
	return (size);
}

char	*ft_utoa_base(unsigned long long n, char *base)
{
	unsigned int		size;
	char				*nbr;
	unsigned long long	nb;
	unsigned int		blen;

	blen = ft_strlen(base);
	size = ft_nbrlen(n, blen);
	nbr = ft_calloc(size + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	nb = n;
	size--;
	if (nb == 0)
		nbr[size] = 48;
	while (nb != 0)
	{
		nbr[size] = base[nb % blen];
		nb /= blen;
		size--;
	}
	return (nbr);
}
