/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 23:46:20 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/20 19:42:53 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*find_linked_room(t_list *room, char *line, char delimiter)
{
	t_room	*tmp;

	while (room)
	{
		tmp = (t_room*)room->content;
		if (!ft_strncmp(line, tmp->name, tmp->name_len))
			if (*(line + tmp->name_len) == delimiter)
				return (tmp);
		room = room->next;
	}
	return (NULL);
}

static int		check_link(t_list *origin, char *line)
{
	t_list	*tmp;
	t_room	*room1;
	t_room	*room2;

	if ((room1 = find_linked_room(origin, line, '-'))
	&& (room2 = find_linked_room(origin, line + room1->name_len + 1, '\0')))
	{
		if (!(tmp = ft_lstnew(room2)))
			return (0);
		ft_lstadd(&room1->neighbors, tmp);
		if (!(tmp = ft_lstnew(room1)))
			return (0);
		ft_lstadd(&room2->neighbors, tmp);
		return (1);
	}
	return (0);
}

int				parse_links(t_list *origin, t_list *lines, char **line)
{
	while (*line)
	{
		if (*line[0] != '#' && !check_link(origin, *line))
			return (0);
		get_next_line(STDIN_FILENO, line);
		if (*line && !save_original_line(&lines, *line))
			return (0);
	}
	return (1);
}
