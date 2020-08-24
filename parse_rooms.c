/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:59:35 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 12:48:26 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		is_valid(char *s1, int c)
{
	int		res;
	char	*s2;

	if (c < 0)
		return (0);
	s2 = ft_itoa(c);
	res = ft_strcmp(s1, s2);
	free(s2);
	return (!res);
}

static int		is_valid_room(t_list **origin, char *line)
{
	t_list	*tmp;
	t_room	*room;
	char	*sep1;
	char	*sep2;

	room = (*origin)->content;
	if (!(sep1 = ft_strchr(line, ' '))
	|| !(sep2 = ft_strchr(sep1 + 1, ' ')))
	{
		free(room);
		tmp = *origin;
		*origin = (*origin)->next;
		free(tmp);
		return (0);
	}
	room->name_len = sep1 - line;
	room->x = ft_atoi(++sep1);
	room->y = ft_atoi(++sep2);
	*(sep2 - 1) = '\0';
	if (!is_valid(sep1, room->x) || !is_valid(sep2, room->y))
		return (0);
	*(sep2 - 1) = ' ';
	return (1);
}

static t_list	*set_new_room(t_list **origin, char *line, int order, char type)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(NULL)))
		return (NULL);
	ft_lstadd(origin, tmp);
	if (!(tmp->content = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	((t_room*)tmp->content)->name = line;
	((t_room*)tmp->content)->neighbors = NULL;
	((t_room*)tmp->content)->order = order;
	((t_room*)tmp->content)->type = type;
	return (tmp);
}

static t_list	*set_border_room(t_list **origin, t_list **lines,
					char *line, char type)
{
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (NULL);
	if (!save_original_line(lines, line))
		return (NULL);
	if (!set_new_room(origin, line, SOURCE, type)
	|| !is_valid_room(origin, line))
		return (NULL);
	return (*origin);
}

int				parse_rooms(t_list **origin, t_list *lines,
					t_list *start_room, t_list *end_room)
{
	char	*line;
	int		size;

	size = 0;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (!save_original_line(&lines, line))
			return (0);
		if (line[0] != '#')
		{
			if (line[0] == 'L' || !set_new_room(origin, line, ++size, MEDIUM))
				return (0);
			if (!is_valid_room(origin, line))
				break ;
		}
		else if ((ft_strcmp(START_ROOM, line) == 0 && (start_room
		|| !(start_room = set_border_room(origin, &lines, line, SOURCE))))
		|| (ft_strcmp(END_ROOM, line) == 0 && (end_room
		|| !(end_room = set_border_room(origin, &lines, line, SINK)))))
			return (0);
	}
	if (!start_room || !end_room || !parse_links(*origin, lines, &line))
		return (0);
	((t_room*)end_room->content)->order = size + 1;
	return (size + 2);
}
