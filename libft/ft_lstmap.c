/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:07:49 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 17:50:15 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;

	tmp = NULL;
	res = NULL;
	while (lst)
	{
		if (tmp)
		{
			if (!(tmp->next = ft_lstnew(f(lst->content))))
			{
				ft_lstdel(&res, del);
				return (NULL);
			}
			tmp = tmp->next;
		}
		else
		{
			if (!(res = ft_lstnew(f(lst->content))))
				return (NULL);
			tmp = res;
		}
		lst = lst->next;
	}
	return (res);
}
