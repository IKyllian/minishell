/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:27:45 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:47:56 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(const char *str)
{
	size_t	size;
	size_t	digit;

	size = 0;
	digit = 0;
	while (str[size])
	{
		if (ft_ishex(str[size]))
			digit++;
		size++;
	}
	return (digit);
}
