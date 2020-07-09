/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:14:19 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/08 17:58:01 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		bfs(t_list **graph, int size, int *level)
{
	int		queue[size];
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
			if (level[(int)cur->content] < 0)
			{
				queue[back++] = (int)cur->content;
				level[(int)cur->content] = level[queue[front]] + 1;
			}
			cur = cur->next;
		}
		++front;
	}
	return (level[size - 1] != NOT_VISITED);
}

static void		save_path(t_list **path, int v)
{
	static t_list	*nodes[MAX_NODES];
	static int		hot_node;

	if (!v)
		return ;
	if (nodes[v])
	{
		if ((int)(*path)->content == hot_node)
			nodes[v]->next = *path;
		*path = nodes[v];
	}
	else
	{
		ft_lstadd(path, ft_lstnew(v));
		nodes[v] = *path;
		hot_node = v;
	}
}

static t_list	*dfs(t_list **graph, int t, int v, int *level)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*path;

	if (v == t)
		return ft_lstnew(t);
	cur = graph[v];
	prev = NULL;
	while (cur)
	{
		if (level[(int)cur->content] == level[v] + 1
		&& (path = dfs(graph, t, (int)cur->content, level)))
		{
			if (prev)
				prev->next = cur->next;
			else
				graph[v] = cur->next;
			ft_lstadd(&graph[(int)cur->content], cur);
			save_path(&path, v);
			return path;
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

t_list			*dinic(t_list **graph, int size, int ants, int *flow)
{
	int		level[size];
	t_list	*path;
	t_list	*paths;

	*flow = 0;
	paths = NULL;
	while (1)
	{
		level[0] = 0;
		ft_memset(level + 1, NOT_VISITED, size - 1);
		if (!bfs(graph, size, level))
			return (paths);
		while ((path = dfs(graph, size - 1, 0, level)))
		{
			ft_lstadd(&paths, ft_lstnew(path));
			if (++(*flow) == ants)
				return (paths);
		}
	}
}
