/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:18:17 by aimelda           #+#    #+#             */
/*   Updated: 2020/06/22 21:47:46 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long long n, int fd)
{
	long long	nb;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	nb = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	while (n / nb >= 10)
		nb *= 10;
	while (nb)
	{
		ft_putchar_fd(n / nb + '0', fd);
		n = n % nb;
		nb /= 10;
	}
}
