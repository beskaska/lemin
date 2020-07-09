/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:57:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/08 22:36:36 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define NOT_VISITED -1
# define START 0
# define INTERMEDIATE 1
# define FINISH 2
# define MAX_NODES 10000

# include "libft/libft.h"
# include <stdio.h> // delete

typedef struct	s_path
{
	t_list	*begin;
	int		length;
	int		lag;
}				t_path;


t_list			*dinic(t_list **graph, int size, int ants, int *flow);
void			print_answer(char **map, t_list *paths, int ants, int flow);

#endif
