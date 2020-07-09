/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:06 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/09 17:54:28 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

static void		del(void *node) {}

static void	freeing(t_list *paths, t_list **graph, char **map, int size)
{
	t_list	*tmp;

	while (paths)
	{
		tmp = paths;
		paths = paths->next;
		ft_lstdel(&(tmp->content), del);
		ft_lstdelone(tmp, del);
	}
	while (--size)
	{
		free(map[size]);
		ft_lstdel(&graph[size + size - 1], del);
		ft_lstdel(&graph[size + size - 2], del);
	}
	free(map[size]);
}

static void	calculate(int size, t_list *origin, int ants)
{
	char	*map[size];
	t_list	*graph[size + size - 2];
	t_list	*paths;
	int		flow;

	/*
	create the map
	do something
	create the graph
	free origin
	*/

	if (!(paths = dinic(graph, size + size - 2, ants, &flow)))
		ft_putstr("ERROR\n");
	else
		print_answer(map, paths, ants, flow);
	freeing(paths, graph, map, size);
}

void	temp(int size)
{
	t_list	*graph[size];

	
}

int			main(void)
{
	int		size;
	int		ants;
	t_list	*origin; // RB-tree or AVL-tree will be faster ~O(log(n))

	// parsing;
	// transform undirected graph to directed graph;
	// remove dead ends;
	// split each intermediate vertex into two vertices
	calculate(size, origin, ants);
}
