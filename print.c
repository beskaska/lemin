/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 21:18:59 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/09 19:29:31 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	prepare(t_list *paths, t_path **way, int size)
{
	int		i;
	t_list	*cur;

	i = 0;
	while (i < size)
	{
		way[i]->begin = paths;
		way[i]->length = 0;
		cur = (t_list*)way[i]->begin->content;
		while (cur)
		{
			++(way[i]->length);
			cur = cur->next;
		}
		paths = paths->next;
		++i;
	}
}

static void	sort_paths(t_path **way, int size) // *** replace by quick sort
{
	int		i;
	int		j;
	int		tmp;
	t_list	*cur;

	i = 0;
	way[i]->lag = 0; // may be separate
	while (i < size - 1)
	{
		j = size - 1;
		while (j > i)
		{
			if (i > j)
			{
				tmp = way[i]->length;
				way[i]->length = way[j]->length;
				way[j]->length = tmp;
				cur = way[i]->begin;
				way[i]->begin = way[j]->begin;
				way[j]->begin = cur;
			}
			--j;
		}
		if (i) // may be separate
			way[i]->lag = way[i - 1]->lag + (way[i]->length - way[i - 1]->length) * i; // may be separate
		++i;
	}
	way[i]->lag = way[i - 1]->lag + (way[i]->length - way[i - 1]->length) * i; // may be separate
}

static void	print_move(int ant, char *room_name)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

void		print_answer(char **map, t_list *paths, int ants, int flow)
{
	t_path	*way[flow];
	t_list	*state[ants];
	int		front_ant;
	int		back_ant;
	int		cur_path;
	int		cur_ant;

	printf("In print answer\n"); //DEL
	prepare(paths, way, flow);
	sort_paths(way, flow);
	front_ant = 0;
	back_ant = 0;
	while (back_ant < ants)
	{
		cur_path = 0;
		cur_ant = front_ant;
		while (front_ant < ants && cur_path < flow)
			if (ants - front_ant - way[cur_path]->lag > 0)
			{
				state[front_ant] = way[cur_path++]->begin;
				print_move(front_ant, map[(int)state[front_ant]->content / 2 + 1]);
				front_ant++;
			}
			else
				flow = cur_path;
		while (cur_ant-- > back_ant)
			if (!(state[cur_ant] = state[cur_ant]->next))
				back_ant = cur_ant + 1;
			else
			{
				state[cur_ant] = state[cur_ant]->next;
				print_move(cur_ant, map[(int)state[cur_ant]->content / 2 + 1]);
			}
		ft_putchar('\n');
	}
}
