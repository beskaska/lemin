/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:18:59 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/07 20:12:55 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	sort_paths(t_path **way, int *length, int size) // *** replace by quick sort
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = size - 1;
		while (j > i)
		{
			if (length[i] > length[j])
			{
				ft_swap(length + i, length + j, sizeof(int));
				ft_swap(&(way[i]->begin), &(way[j]->begin), sizeof(t_list));
			}
			--j;
		}
		++i;
	}
	i = 0;
	while (++i < size)
		way[i]->lag = (way[i - 1]->lag + (length[i] - length[i - 1]) * i) / 2;
}

static int	prepare_paths(t_list *paths, t_path **way, int *size)
{
	t_list	*cur;
	int		length[*size];
	int		i;

	i = 0;
	while (i < *size)
	{
		if (!(way[i] = (t_path*)malloc(sizeof(t_path))))
			return ((*size = i) && 0);
		way[i]->begin = paths->content;
		way[i]->lag = 0;
		length[i] = 0;
		cur = (t_list*)way[i]->begin;
		while (cur)
		{
			++length[i];
			cur = cur->next;
		}
		paths = paths->next;
		++i;
	}
	sort_paths(way, length, *size);
	return (1);
}

static void	print_move(int ant, char **map, t_list **state)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(map[(int)state[ant]->content / 2 + 1]);
	ft_putchar(' ');
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
			//printf("L%d-%s ", cur_ant, map[(int)state[cur_ant]->content / 2 + 1]); and everywhere
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
			if (ants - front_ant - way[cur]->lag >= 0)
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
