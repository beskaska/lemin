/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 20:33:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 20:54:40 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The function reallocate memory and copy data from old memory area
*/

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;
	size_t	i;
	size_t	comparator;

	if ((new_ptr = malloc(new_size)))
	{
		i = 0;
		if (new_size <= old_size)
			comparator = new_size;
		else
		{
			comparator = old_size;
			ft_bzero(new_ptr + old_size, new_size - old_size);
		}
		while (i < comparator)
		{
			((unsigned char*)new_ptr)[i] = ((unsigned char*)ptr)[i];
			++i;
		}
	}
	free(ptr);
	return (new_ptr);
}
