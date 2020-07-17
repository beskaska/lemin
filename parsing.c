/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:58:14 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/15 19:56:01 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		del(void *node)
{
	free(node);
}

static int		freeing(t_list *lines, t_list *origin)
{
	ft_lstdel(&lines, del);
	ft_lstdel(&origin, del);
	return (0);
}



int				parse_links(t_list *origin, t_list *lines, char **line)
{
	while (*line)
	{
		// add the line to the lines
		if (line[0] != '#' && !check_link(origin, *line))
			return (0);
		get_next_line(STDOUT_FILENO, line);
	}
	return (1);
}

int				parsing(t_list *origin, size_t *size, int *ants) // may be return origin???
{
	t_list	*lines;
	char	*line;

	if (get_next_line(STDOUT_FILENO, &line) <= 0 || (*ants = ft_atoi(line)) <= 0
	|| ft_strcmp(ft_itoa(ants), line))
		return (0); // free(line)
	if (!(lines = ft_lstnew(line)))
		return (0); // free(line)
	origin = NULL;
	if (!(*size = parse_rooms(&origin, lines, &line)))
		return (freeing(lines, origin));
	
}
