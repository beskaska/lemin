/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:59:35 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/20 19:17:07 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		is_valid_room(t_list **origin, char *line)
{
	t_list	*tmp;
	t_room	*room;
	char	*sep1;
	char	*sep2;

	room = (*origin)->content;
	if (!(sep1 = ft_strchr(line, ' ')) || !(sep2 = ft_strchr(sep1 + 1, ' ')))
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
	/*(sep2 - 1) = '\0';
	if (ft_strcmp(sep1, ft_itoa(room->x)) || ft_strcmp(sep2, ft_itoa(room->y)))
		return (NULL); // leaks and not correct
	*(sep2 - 1) = ' ';*/
	return (1);
}

static t_list	*set_new_room(t_list **origin, char *line, int order, char type)
{
	t_room	*room;
	t_list	*tmp;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = line;
	room->neighbors = NULL;
	room->order = order;
	room->type = type;
	if (!(tmp = ft_lstnew(room)))
	{
		free(room);
		return (NULL);
	}
	ft_lstadd(origin, tmp);
	return (tmp);
}

static t_list	*set_border_room(t_list **origin, t_list **lines, char *line, char type)
{
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (NULL);
	if (!save_original_line(lines, line))
		return (NULL);
	if (!set_new_room(origin, line, SOURCE, type) || !is_valid_room(origin, line))
		return (NULL);
	return (*origin);
}

int				parse_rooms(t_list **origin, t_list *lines, char **line)
{
	t_list	*start_room;
	t_list	*end_room;
	int		size;

	start_room = NULL;
	end_room = NULL;
	size = 0;
	while (get_next_line(STDIN_FILENO, line) > 0)
	{
		if (!save_original_line(&lines, *line))
			return (0);
		if (*line[0] != '#')
		{
			if (*line[0] == 'L' || !set_new_room(origin, *line, ++size, INTERMEDIATE))
				return (0);
			if (!is_valid_room(origin, *line))
				break ;
		}
		else if ((ft_strcmp(START_ROOM, *line) == 0 && (start_room
		|| !(start_room = set_border_room(origin, &lines, *line, SOURCE))))
		|| (ft_strcmp(END_ROOM, *line) == 0 && (end_room
		|| !(end_room = set_border_room(origin, &lines, *line, SINK)))))
			return (0);
	}
	if (!start_room || !end_room || !parse_links(*origin, lines, line))
		return (0);
	((t_room*)end_room->content)->order = size + 1;
	return (size + 2);
}
