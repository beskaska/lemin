/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:14:37 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 13:48:22 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	det_sign(const char **str)
{
	if (**str == '-')
	{
		++(*str);
		return (-1);
	}
	else if (**str == '+')
		++(*str);
	return (1);
}

int			ft_atoi(const char *str)
{
	size_t	res;
	int		sign;

	while (ft_isspace(*str))
		++str;
	res = 0;
	sign = det_sign(&str);
	while (ft_isdigit(*str))
	{
		if (res > INT64_MAX / 10
		|| (res == INT64_MAX / 10 && *str - '0' > INT64_MAX % 10))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + *str - '0';
		str++;
	}
	if (sign == 1)
		return (res);
	return (0 - res);
}
