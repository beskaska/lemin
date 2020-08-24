/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:58:14 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 12:46:52 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				save_original_line(t_list **lines, char *line)
{
	t_list	*new_line;

	if (!(new_line = ft_lstnew(line)))
	{
		free(line);
		return (0);
	}
	ft_lstadd_back(lines, new_line);
	*lines = (*lines)->next;
	return (1);
}

static void		del_room(void *node)
{
	ft_lstdel(&((t_room*)node)->neighbors, NULL);
	free(node);
}

static int		is_valid(char *s1, char *s2)
{
	int		res;

	res = ft_strcmp(s1, s2);
	free(s1);
	return (!res);
}

t_list			*parsing(t_list **lines, size_t *size, int *ants)
{
	t_list	*origin;
	char	*line;

	origin = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (NULL);
	if ((*ants = ft_atoi(line)) <= 0 || !is_valid(ft_itoa(*ants), line)
	|| !(*lines = ft_lstnew(line)))
		free(line);
	else if (!(*size = parse_rooms(&origin, *lines, NULL, NULL)))
	{
		ft_lstdel(lines, free);
		ft_lstdel(&origin, del_room);
	}
	return (origin);
}
