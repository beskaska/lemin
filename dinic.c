/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:14:19 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/11 11:26:18 by aimelda          ###   ########.fr       */
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

static t_list	*dfs(t_list **graph, t_list *dad, size_t t, int *level)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*path;

	printf("in DFS: v = %zu, level[v] = %d\n", (size_t)dad->content, level[(size_t)dad->content]); // DEL
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
			ft_lstadd(&graph[(size_t)cur->content], dad);
			save_path(&path, (size_t)dad->content);
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
	t_list	*tmp; //DEL

	*flow = 0;
	paths = NULL;
	while (1)
	{
		printf("flow = %d\n", *flow); // DEL
		// test
			for (int i = 0; i < size; i++)
			{
				printf("%d: ", i);
				tmp = graph[i];
				while (tmp)
				{
					printf("%zu ", (size_t)tmp->content);
					tmp = tmp->next;
				}
				printf("\n");
			}
			// test
		level[0] = 0;
		ft_memset(level + 1, NOT_VISITED, (size - 1) * sizeof(int));
		if (!bfs(graph, size, level))
			return (paths);
		for (int i = 0; i < size; i++)
		{
			printf("level[%d] = %d\n", i, level[i]); // DEL
		}
		while ((path = dfs(graph, graph[0], size - 1, level)))
		{
			ft_lstadd(&paths, ft_lstnew(path));
			if (++(*flow) == ants)
				return (paths);
		}
	}
}
