/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/07 19:27:21 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define MAX_ROOMS 100000
# define NOT_VISITED -1
# define START_ROOM "##start"
# define END_ROOM "##end"
# define SOURCE 0
# define SINK 1
# define INTERMEDIATE 2
# define ERR_MSG "ERROR\n"

# include "libft/libft.h"
# include <stdio.h> // delete

typedef struct	s_room
{
	char	*name;
	t_list	*neighbors;
	size_t	order;
	int		name_len;
	int		x;
	int		y;
	char	type;
}				t_room;

typedef struct	s_path
{
	t_list	*begin; // the first node of the path
	int		lag; // length difference between current path and the first (shortest) path --- incorrect
}				t_path;

t_list			*parsing(t_list **lines, size_t *size, int *ants);
int				parse_rooms(t_list **origin, t_list *lines);
int				parse_links(t_list *origin, t_list *lines, char **line);
int				save_original_line(t_list **lines, char *line);
void			evaluate(t_list *origin, t_list *lines, size_t size, int ants);
t_list			*dinic(t_list **graph, size_t size, int ants, int *flow);
void			print_answer(char **map, t_list *paths, int ants, int flow);

#endif
