/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:18:59 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/12 13:34:46 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	sort_paths(t_path **way, int *length, int size) // *** replace by quick sort
{
	int		i;
	int		j;
	int		tmp;
	t_list	*cur;

	i = 0;
	way[i]->lag = 0; // may be out of this function
	while (i < size - 1)
	{
		j = size - 1;
		while (j > i)
		{
			if (i > j)
			{
				tmp = length[i];
				length[i] = length[j];
				length[j] = tmp;
				cur = way[i]->begin;
				way[i]->begin = way[j]->begin;
				way[j]->begin = cur;
			}
			--j;
		}
		++i;
		way[i]->lag = way[i - 1]->lag + (length[i] - length[i - 1]) * i; // may be out of this function
	}
}

static void	prepare(t_list *paths, t_path **way, int size)
{
	t_list	*cur;
	int		length[size];
	int		i;

	i = 0;
	while (i < size)
	{
		way[i] = (t_path*)malloc(sizeof(t_path*)); // check if memory is allocated
		way[i]->begin = paths->content;
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
	sort_paths(way, length, size);
}

static void	print_move(int ant, char *room_name)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

void		move_ants_on_way(t_list **state, char **map, int *back, int front)
{
	int		cur_ant;

	cur_ant = *back - 1;
	while (++cur_ant < front)
		if (!(state[cur_ant]->next))
			*back = cur_ant + 1;
		else
		{
			state[cur_ant] = state[cur_ant]->next->next;
			print_move(cur_ant, map[(int)state[cur_ant]->content / 2 + 1]);
		}
}

void		print_answer(char **map, t_list *paths, int ants, int flow)
{
	t_path	*way[flow];
	t_list	*state[ants];
	int		front_ant;
	int		back_ant;
	int		cur;

	prepare(paths, way, flow);
	front_ant = 1;
	back_ant = 1;
	while (back_ant < ants)
	{
		move_ants_on_way(state, map, &back_ant, front_ant);
		cur = 0;
		while (front_ant < ants && cur < flow)
			if (ants - front_ant - way[cur]->lag > 0)
			{
				state[front_ant] = way[cur++]->begin;
				print_move(front_ant, map[(int)state[front_ant]->content / 2 + 1]);
				front_ant++;
			}
			else
				while (flow > cur)
					free(way[--flow]);
		ft_putchar('\n');
	}
	while (flow--)
		free(way[flow]);
}
