/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 12:33:04 by ctaleb            #+#    #+#             */
/*   Updated: 2021/03/19 14:52:09 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*new;

	newlst = NULL;
	while (lst)
	{
		new = NULL;
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&newlst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&newlst, new);
		lst = lst->next;
	}
	return (newlst);
}
