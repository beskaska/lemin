/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/12 22:20:05 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define NOT_VISITED -1
# define MAX_ROOMS 20000
# define START_ROOM "##start"
# define END_ROOM "##end"

# include "libft/libft.h"
# include <stdio.h> // delete

typedef struct s_room
{
	char	*name;
	t_list	*neighbors;
}				t_room;

typedef struct	s_path
{
	t_list	*begin; // the first node of the path
	int		lag; // length difference between current path and the first (shortest) path --- incorrect
}				t_path;

int				parsing(t_list *origin, size_t *size, int *ants);
t_list			*dinic(t_list **graph, size_t size, int ants, int *flow);
void			print_answer(char **map, t_list *paths, int ants, int flow);

#endif
