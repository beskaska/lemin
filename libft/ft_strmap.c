/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 23:25:07 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 17:24:39 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	if (s)
	{
		i = 0;
		res = (char*)malloc(ft_strlen(s) + 1);
		if (res)
		{
			while (*s != '\0')
				res[i++] = f(*s++);
			res[i] = '\0';
		}
		return (res);
	}
	return (NULL);
}
