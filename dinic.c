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

static void		save_path(t_list **path, size_t v)
{
	static t_list	*nodes[MAX_NODES];
	static size_t	hot_node;

	if (!v)
		return ;
	if (nodes[v])
	{
		if ((size_t)(*path)->content == hot_node)
			nodes[v]->next = *path;
		*path = nodes[v];
	}
	else
	{
		ft_lstadd(path, ft_lstnew((void*)v));
		nodes[v] = *path;
		hot_node = v;
	}
}

static t_list	*dfs(t_list **graph, size_t t, size_t v, int *level)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*path;

	printf("in DFS: v = %zu, level[v] = %d\n", v, level[v]); // DEL
	if (v == t)
		return ft_lstnew((void*)t);
	cur = graph[v];
	prev = NULL;
	while (cur)
	{
		if (level[(size_t)cur->content] == level[v] + 1
		&& (path = dfs(graph, t, (size_t)cur->content, level)))
		{
			if (prev)
				prev->next = cur->next;
			else
				graph[v] = cur->next;
			ft_lstadd(&graph[(size_t)cur->content], cur);
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
		printf("flow = %d\n", *flow); // DEL
		level[0] = 0;
		ft_memset(level + 1, NOT_VISITED, (size - 1) * sizeof(int));
		if (!bfs(graph, size, level))
			return (paths);
		for (int i = 0; i < size; i++)
		{
			printf("level[%d] = %d\n", i, level[i]); // DEL
		}
		while ((path = dfs(graph, size - 1, 0, level)))
		{
			ft_lstadd(&paths, ft_lstnew(path));
			if (++(*flow) == ants)
				return (paths);
		}
	}
}
