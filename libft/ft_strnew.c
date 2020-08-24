/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:16:24 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/24 15:10:03 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	if (size + 1 == 0)
	{
		ft_putendl_fd("Err: Maximum length of string exceeded", STDERR_FILENO);
		return (NULL);
	}
	return ((char*)ft_memalloc(size + 1));
}
