/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/24 17:47:02 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"

# define MAX_ROOMS 20000
# define NOT_VISITED (-1)
# define START_ROOM "##start"
# define END_ROOM "##end"
# define SOURCE 0
# define SINK 1
# define MEDIUM 2
# define ERR_MSG "ERROR\n"

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
	t_list	*begin;
	int		lag;
}				t_path;

t_list			*parsing(t_list **lines, size_t *size, int *ants);
int				parse_rooms(t_list **origin, t_list *lines,
					t_list *start_room, t_list *end_room);
int				parse_links(t_list *origin, t_list *lines, char **line);
int				save_original_line(t_list **lines, char *line);
void			evaluate(t_list *origin, t_list *lines, size_t size, int ants);
t_list			*dinic(t_list **graph, size_t size, int ants, int *flow);
void			print_answer(char **map, t_list *paths, int ants, int flow);
void			print_move(int ant, char **map, t_list **state);

#endif
