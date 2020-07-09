/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:06:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/17 23:33:39 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		tmp = tmp->next;
		ft_lstdelone(*alst, del);
		*alst = tmp;
	}
}
