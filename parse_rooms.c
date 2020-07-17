/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:59:35 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/15 19:55:04 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int      freeing(t_list *start_room, t_list *end_room, char *line)
{
	if (start_room)
	{
		free(start_room->content);
		free(start_room);
	}
	if (end_room)
	{
		free(end_room->content);
		free(end_room);
	}
	free(line);
	return (0);
}

static t_list	*get_new_room(char *line)
{
	t_room	*room;
	t_list	*tmp;
	char	*sep_1;
	char	*sep_2;

	if (!(sep_1 = ft_strchr(*line, ' ')) || !(sep_2 = ft_strchr(*sep_1, ' ')))
		return (NULL);
	if (!(room = (t_room*)malloc(sizeof(t_room*))))
		return (NULL);
	if (!(tmp = ft_lstnew(room)))
		free(room);
	room->name = line;
	room->sep = sep_1;
	return (tmp);
}

static t_list	*get_border_room(t_list **lines, char **line)
{
	t_list	*new_line;

	if (!(new_line = ft_lstnew(*line)))
		return (NULL);
	ft_lstadd_back(lines, new_line);
	*lines = (*lines)->next;
	if (get_next_line(STDOUT_FILENO, line) <= 0)
		return (NULL);
	return (get_new_room(*line));
}

int		        parse_rooms(t_list **origin, t_list *lines, char **line)
{
	t_list	*start_room;
	t_list	*end_room;
	t_list	*back;
	t_list	*tmp;
	char	*separator;
	int		size;

	start_room = NULL;
	end_room = NULL;
	size = 0;
	while (get_next_line(STDOUT_FILENO, line) > 0)
	{
		if (*line[0] == '#')
		{
			if ((ft_strcmp(START_ROOM, *line) == 0
			&& (start_room || !(start_room = get_border_room(&lines, line))))
			|| (ft_strcmp(END_ROOM, *line) == 0
			&& (end_room || !(end_room = get_border_room(&lines, line)))))
				return (freeing(start_room, end_room, *line)); // free lines and origin
		}
		else
		{
			if (*line[0] == 'L' || !(tmp = get_new_room(*line)))
				return (freeing(start_room, end_room, *line)); // free lines and origin
			ft_lstadd(origin, tmp);
			++size;
		}
		if (!(tmp = ft_lstnew(*line)))
			return (freeing(start_room, end_room, *line)); // free lines and origin
		ft_lstadd_back(&lines, tmp);
		lines = lines->next;
	}
	if (!start_room || !end_room)
		return (freeing(start_room, end_room, *line)); // free lines and origin
	ft_lstadd(origin, start_room);
	ft_lstadd_back(origin, end_room); // not efficient
	return (size + 2);
}
