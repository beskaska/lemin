/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:06 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/24 17:28:29 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_input(void *line)
{
	ft_putendl(line);
}

void		print_move(int ant, char **map, t_list **state)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(map[(int)state[ant]->content / 2 + 1]);
	ft_putchar(' ');
}

int			main(void)
{
	t_list	*origin;
	t_list	*lines;
	size_t	size;
	int		ants;

	if (!(origin = parsing(&lines, &size, &ants)))
		ft_putstr(ERR_MSG);
	else
	{
		ft_lstiter(lines, print_input);
		evaluate(origin, lines, size, ants);
	}
}
