/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:58:42 by ctaleb            #+#    #+#             */
/*   Updated: 2020/11/27 11:05:37 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	max;

	i = 0;
	max = ft_lstsize(lst);
	while (i < max - 1)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}
