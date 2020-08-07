/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:06 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/22 23:02:21 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	print_input(void *line)
{
	ft_putendl(line);
}

int			main(void)
{
	t_list	*origin; // RB-tree or AVL-tree will be faster ~O(log(n))
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
