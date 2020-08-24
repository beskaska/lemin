/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:41:18 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 13:53:45 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned char	tmp;
	size_t			i;

	ptr1 = a;
	ptr2 = b;
	i = 0;
	while (i < size)
	{
		tmp = ptr1[i];
		ptr1[i] = ptr2[i];
		ptr2[i] = tmp;
		++i;
	}
}
