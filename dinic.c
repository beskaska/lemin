/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:14:19 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/12 21:20:26 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		bfs(t_list **graph, size_t size, int *level)
{
	size_t	queue[size];
	int		front;
	int		back;
	t_list	*cur;

	back = 0;
	front = 0;
	queue[back++] = 0;
	while (front < back)
	{
		cur = graph[queue[front]];
		while (cur)
		{
			if (level[(size_t)cur->content] < 0)
			{
				queue[back++] = (size_t)cur->content;
				level[(size_t)cur->content] = level[queue[front]] + 1;
			}
			cur = cur->next;
		}
		++front;
	}
	return (level[size - 1] != NOT_VISITED);
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

static t_list	*dfs(t_list **graph, t_list *dad, size_t t, int *level)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*path;

	if ((size_t)dad->content == t)
		return ft_lstnew((void*)t);
	cur = graph[(size_t)dad->content];
	prev = NULL;
	while (cur)
	{
		if (level[(size_t)cur->content] == level[(size_t)dad->content] + 1
		&& (path = dfs(graph, cur, t, level)))
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
	int		level[size];
	t_list	*path;
	t_list	*paths;

	*flow = 0;
	paths = NULL;
	level[0] = 0;
	while (1)
	{
		ft_memset(level + 1, NOT_VISITED, (size - 1) * sizeof(int));
		if (!bfs(graph, size, level))
			return (paths);
		while ((path = dfs(graph, graph[0], size - 1, level)))
		{
			if (!(path = ft_lstnew(path)))
				return (NULL);
			ft_lstadd(&paths, path);
			if (++(*flow) == ants)
				return (paths);
		}
	}
}
