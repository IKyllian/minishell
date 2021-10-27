/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:07:23 by ctaleb            #+#    #+#             */
/*   Updated: 2021/10/27 10:13:50 by kdelport         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		size;

	size = ft_strlen((char *)str) + 1;
	cpy = ft_calloc(size, sizeof(char));
	if (!cpy)
		return (NULL);
	if (ft_memcpy(cpy, str, size - 1) == NULL)
		return (NULL);
	return (cpy);
}
