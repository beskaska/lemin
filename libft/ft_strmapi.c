/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:27:15 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 17:24:47 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			{
				res[i] = f(i, *s++);
				i++;
			}
			res[i] = '\0';
		}
		return (res);
	}
	return (NULL);
}
