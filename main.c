/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:06 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/15 21:35:29 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

static void		del(void *node)
{
	node = NULL;
}

static void	freeing(t_list *paths, t_list **graph, char **map, int size)
{
	t_list	*tmp;

	while (paths)
	{
		tmp = paths;
		paths = paths->next;
		ft_lstdel((t_list**)(&tmp->content), del);
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

static void	calculate(size_t size, t_list *origin, int ants)
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

	// testing
	origin = NULL;
	map[0] = "start";
	map[1] = "1";
	map[2] = "2";
	map[3] = "3";
	map[4] = "4";
	map[5] = "5";
	map[6] = "6";
	map[7] = "finish";
	for (size_t i = 0; i < size + size - 2; i++)
		graph[i] = NULL;
	ft_lstadd(&graph[0], ft_lstnew((void*)1));
	ft_lstadd(&graph[0], ft_lstnew((void*)3));
	ft_lstadd(&graph[0], ft_lstnew((void*)0));
	ft_lstadd(&graph[1], ft_lstnew((void*)2));
	ft_lstadd(&graph[2], ft_lstnew((void*)7));
	ft_lstadd(&graph[3], ft_lstnew((void*)4));
	ft_lstadd(&graph[4], ft_lstnew((void*)5));
	ft_lstadd(&graph[4], ft_lstnew((void*)9));
	ft_lstadd(&graph[5], ft_lstnew((void*)6));
	ft_lstadd(&graph[6], ft_lstnew((void*)11));
	ft_lstadd(&graph[7], ft_lstnew((void*)8));
	ft_lstadd(&graph[8], ft_lstnew((void*)9));
	ft_lstadd(&graph[9], ft_lstnew((void*)10));
	ft_lstadd(&graph[10], ft_lstnew((void*)13));
	ft_lstadd(&graph[11], ft_lstnew((void*)12));
	ft_lstadd(&graph[12], ft_lstnew((void*)13));
	// testing

	if (!(paths = dinic(graph, size + size - 2, ants, &flow)))
		ft_putstr("ERROR\n");
	else
		print_answer(map, paths, ants + 1, flow);
	freeing(paths, graph, map, size);
}

int			main(void)
{
	size_t	size;
	int		ants;
	t_list	*origin; // RB-tree or AVL-tree will be faster ~O(log(n))

	origin = NULL;
	if (!parsing(origin, size, ants))
		return (0); // ERROR
	// transform undirected graph to directed graph;
	// remove dead ends;
	// split each intermediate vertex into two vertices

	// testing
	ants = 4;
	size = 8;
	// testing
	calculate(size, origin, ants);
}
