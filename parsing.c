/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:58:14 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/13 19:04:00 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		freeing(t_list *lines)
{
	
}

int				parsing(t_list *origin, size_t *size, int *ants)
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
		return (0); // free lines, origin
	
}
