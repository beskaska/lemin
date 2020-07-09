/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:18:12 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/17 22:42:44 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list*)malloc(sizeof(*res));
	if (res)
	{
		if (content)
			res->content = content;
		else
			res->content = NULL;
		res->next = NULL;
	}
	return (res);
}
