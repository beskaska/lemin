/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:08:00 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 21:47:38 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	long long	nb;

	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	nb = 1;
	if (n < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	while (n / nb >= 10)
		nb *= 10;
	while (nb)
	{
		ft_putchar(n / nb + '0');
		n = n % nb;
		nb /= 10;
	}
}
