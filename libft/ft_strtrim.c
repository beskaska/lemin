/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:54:36 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/17 23:46:57 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*res;

	if (!s)
		return (NULL);
	while (ft_isspace(*s))
		s++;
	len = ft_strlen(s);
	if (len)
		while (ft_isspace(s[len - 1]))
			len--;
	res = (char*)malloc(len + 1);
	if (res)
	{
		res[len] = '\0';
		return (ft_strncpy(res, s, len));
	}
	return (NULL);
}
