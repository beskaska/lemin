/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:14:19 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/22 18:53:33 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		bfs(t_list **graph, size_t size, int *pred)
{
	size_t	queue[size];
	int		front;
	int		back;
	t_list	*cur;

	back = 0;
	front = 0;
	queue[back++] = SOURCE;
	while (front < back)
	{
		cur = graph[queue[front]];
		while (cur)
		{
			if (pred[(size_t)cur->content] == NOT_VISITED)
			{
				queue[back++] = (size_t)cur->content;
				pred[(size_t)cur->content] = (int)queue[front];
			}
			cur = cur->next;
		}
		++front;
	}
	return (pred[size - 1] != NOT_VISITED);
}

static t_list	*save_path(t_list **path, size_t v)
{
	static t_list	*nodes[MAX_ROOMS + MAX_ROOMS];
	static size_t	hot_node;
	t_list			*tmp;

	if (!v)
		return (*path);
	if (nodes[v])
	{
		if ((size_t)(*path)->content == hot_node)
			nodes[v]->next = *path;
		*path = nodes[v];
	}
	else
	{
		if (!(tmp = ft_lstnew((void*)v)))
			return (NULL);
		ft_lstadd(path, tmp);
		nodes[v] = *path;
		hot_node = v;
	}
	return (*path);
}

static t_list	*dfs(t_list **graph, t_list *dad, size_t t, int *pred)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*path;

	if ((size_t)dad->content == t)
		return (ft_lstnew((void*)t));
	cur = graph[(size_t)dad->content];
	prev = NULL;
	while (cur)
	{
		if ((size_t)pred[(size_t)cur->content] == (size_t)dad->content
		&& (path = dfs(graph, cur, t, pred)))
		{
			if (prev)
				prev->next = cur->next;
			else
				graph[(size_t)dad->content] = cur->next;
			ft_lstadd(&graph[(size_t)cur->content], cur);
			cur->content = dad->content;
			return (save_path(&path, (size_t)dad->content));
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

t_list			*dinic(t_list **graph, size_t size, int ants, int *flow)
{
	int		pred[size];
	t_list	*path;
	t_list	*paths;

	*flow = 0;
	paths = NULL;
	pred[SOURCE] = MAX_ROOMS + MAX_ROOMS;
	while (1)
	{
		ft_memset(pred + 1, NOT_VISITED, (size - 1) * sizeof(*pred));
		if (!bfs(graph, size, pred))
			return (paths);
		while ((path = dfs(graph, graph[SOURCE], size - 1, pred)))
		{
			if (!(path = ft_lstnew(path)))
				return (NULL);
			ft_lstadd(&paths, path);
			if (++(*flow) == ants)
				return (paths);
		}
	}
}
