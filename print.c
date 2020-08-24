/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:18:59 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/24 17:47:48 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	sort_paths(t_path **way, int *length, int first, int last)
{
	int		i;
	int		j;
	int		pivot;

	if (first >= last)
		return ;
	pivot = first;
	i = first;
	j = last;
	while (i < j)
	{
		while (length[i] <= length[pivot] && i < last)
			++i;
		while (length[j] > length[pivot])
			--j;
		if (i < j)
		{
			ft_swap(length + i, length + j, sizeof(int));
			ft_swap(&(way[i]->begin), &(way[j]->begin), sizeof(t_list));
		}
	}
	ft_swap(length + pivot, length + j, sizeof(int));
	ft_swap(&(way[pivot]->begin), &(way[j]->begin), sizeof(t_list));
	sort_paths(way, length, first, j - 1);
	sort_paths(way, length, j + 1, last);
}

static int	prepare_paths(t_list *paths, t_path **way, int *size)
{
	t_list	*cur;
	int		length[*size];
	int		i;

	i = -1;
	while (++i < *size)
	{
		if (!(way[i] = (t_path*)ft_memalloc(sizeof(t_path))))
			return ((*size = i) * 0);
		way[i]->begin = paths->content;
		length[i] = 0;
		cur = (t_list*)way[i]->begin;
		while (cur)
		{
			++length[i];
			cur = cur->next;
		}
		length[i] = length[i] / 2 + 1;
		paths = paths->next;
	}
	sort_paths(way, length, 0, *size - 1);
	i = 0;
	while (++i < *size)
		way[i]->lag = way[i - 1]->lag + (length[i] - length[i - 1]) * i;
	return (1);
}

void		move_ants_on_way(t_list **state, char **map, int *back, int front)
{
	int		cur_ant;

	cur_ant = *back - 1;
	ft_putchar('\n');
	while (++cur_ant < front && !state[cur_ant]->next)
		++(*back);
	while (cur_ant < front)
	{
		if (state[cur_ant]->next)
		{
			state[cur_ant] = state[cur_ant]->next->next;
			print_move(cur_ant, map, state);
		}
		++cur_ant;
	}
}

void		move_ants(char **map, t_path **way, int ants, int *flow)
{
	t_list	*state[ants];
	int		front_ant;
	int		back_ant;
	int		cur;

	cur = ants;
	while (cur--)
		state[cur] = NULL;
	front_ant = 1;
	back_ant = 1;
	while (back_ant < ants)
	{
		move_ants_on_way(state, map, &back_ant, front_ant);
		cur = 0;
		while (front_ant < ants && cur < *flow)
			if (ants - front_ant >= way[cur]->lag)
			{
				state[front_ant] = way[cur++]->begin;
				print_move(front_ant++, map, state);
			}
			else
				while (*flow > cur)
					free(way[--(*flow)]);
	}
}

void		print_answer(char **map, t_list *paths, int ants, int flow)
{
	t_path	*way[flow];

	if (!prepare_paths(paths, way, &flow))
		ft_putstr("ERROR\n");
	else
		move_ants(map, way, ants, &flow);
	while (flow--)
		free(way[flow]);
}
