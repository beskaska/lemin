/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:58:14 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/13 13:53:37 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	parse_rooms(t_list **origin, t_list *lines)
{
	t_list	*start_room;
	t_list	*end_room;
	t_list	*back;
	t_room	*room;
	char	*line;

	start_room = NULL;
	end_room = NULL;
	while (get_next_line(STDOUT_FILENO, &line) > 0) // need to be distinguished from links
	{
		if (line[0] == '#')
		{
			if (ft_strcmp(START_ROOM, line) == 0)
			{
				if (start_room || !(room = (t_room*)malloc(sizeof(t_room*))))
					return (0);
				start_room = origin; // may be it's useless
			}
			else if (ft_strcmp(END_ROOM, line) == 0)
			{
				if (end_room || !(room = (t_room*)malloc(sizeof(t_room*))))
					return (0);
			}
		}
		ft_lstadd(origin, ft_lstnew(room)); // check if lstnew == NULL
		ft_lstadd_back(&lines, ft_lstnew(line)); // check if lstnew == NULL
		lines = lines->next;
	}
}

int			parsing(t_list *origin, size_t *size, int *ants)
{
	t_list	*lines;
	char	*line;

	if (get_next_line(STDOUT_FILENO, &line) <= 0 || (*ants = ft_atoi(line)) <= 0
	|| ft_strcmp(ft_itoa(ants), line))
		return (0);
	if (!(lines = ft_lstnew(line)))
		return (0);
	origin = NULL;
	if (!(*size = parse_rooms(&origin, lines)))
		return (0);
	
}
