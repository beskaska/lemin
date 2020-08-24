/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 19:59:27 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 12:48:41 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	free_origin(t_list *origin)
{
	t_list	*tmp;
	t_room	*room;

	while (origin)
	{
		tmp = origin;
		origin = origin->next;
		room = (t_room*)tmp->content;
		*(room->name + room->name_len) = 0;
		ft_lstdel(&room->neighbors, NULL);
		free(tmp->content);
		free(tmp);
	}
	return (1);
}

static void	freeing(t_list *paths, t_list **graph, t_list *lines, int size)
{
	t_list	*tmp;

	while (paths)
	{
		tmp = paths;
		paths = paths->next;
		ft_lstdel((t_list**)(&tmp->content), NULL);
		free(tmp);
	}
	while (--size)
	{
		ft_lstdel(&graph[size + size - 1], NULL);
		ft_lstdel(&graph[size + size - 2], NULL);
	}
	ft_lstdel(&lines, free);
}

static int	save_links(t_list **graph, t_list *links, size_t index)
{
	t_list	*tmp;
	t_room	*room;

	if (index != SOURCE)
	{
		if (!(tmp = ft_lstnew((void*)(index + 1))))
			return (0);
		ft_lstadd(&graph[index], tmp);
		++index;
	}
	while (links)
	{
		room = (t_room*)links->content;
		if (room->order)
		{
			if (!(tmp = ft_lstnew((void*)(room->order + room->order - 1))))
				return (0);
			ft_lstadd(&graph[index], tmp);
		}
		links = links->next;
	}
	return (1);
}

static int	make_graph(t_list *origin, char **map, t_list **graph, size_t size)
{
	t_list	*room;
	t_room	*cur;
	size_t	i;

	i = 0;
	while (i < size + size - 2)
		graph[i++] = NULL;
	room = origin;
	while (room)
	{
		cur = (t_room*)room->content;
		if (cur->type == MEDIUM
		&& !save_links(graph, cur->neighbors, cur->order + cur->order - 1))
			return (!free_origin(origin));
		else if (cur->type == SOURCE
		&& !save_links(graph, cur->neighbors, SOURCE))
			return (!free_origin(origin));
		map[cur->order] = cur->name;
		room = room->next;
	}
	ft_lstadd(&graph[SOURCE], ft_lstnew((void*)SOURCE));
	return (free_origin(origin));
}

void		evaluate(t_list *origin, t_list *lines, size_t size, int ants)
{
	char	*map[size];
	t_list	*graph[size + size - 2];
	t_list	*paths;
	int		flow;

	paths = NULL;
	if (!make_graph(origin, map, graph, size)
	|| !(paths = dinic(graph, size + size - 2, ants, &flow)))
	{
		ft_putchar('\n');
		ft_putstr(ERR_MSG);
	}
	else
		print_answer(map, paths, ants + 1, flow);
	freeing(paths, graph, lines, size);
}
