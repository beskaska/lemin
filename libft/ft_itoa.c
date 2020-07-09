/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:35:13 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 21:46:20 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long n)
{
	int			len;
	long long	nb;
	char		*res;

	len = 1;
	nb = n / 10;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	if (n < 0)
		++len;
	if (!(res = (char*)malloc(len + 1)))
		return (NULL);
	res[len] = '\0';
	res[0] = '-';
	if (!n)
		res[0] = '0';
	while (n)
	{
		res[--len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (res);
}
