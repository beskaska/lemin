/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:44:50 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/23 14:00:46 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The function returns:
** -1	- if an error has happened
** 0	- if the reading has been completed
** 1	- if a line has been read and the line terminates with EOL
** 2	- if a line has been read and the line terminates with EOF
*/

static void		del(void *st)
{
	free(((t_fd*)st)->txt);
	free(st);
}

static int		fd_new(char *str, int fd, t_list **fd_lst)
{
	t_list	*tmp;

	if (*fd_lst && ((t_fd*)((*fd_lst)->content))->fd == fd)
	{
		((t_fd*)((*fd_lst)->content))->cur = str;
		return (1);
	}
	if (!(tmp = ft_lstnew(NULL)))
		return (0);
	if (!(tmp->content = (t_fd*)malloc(sizeof(t_fd))))
		return (0);
	if (!(((t_fd*)tmp->content)->txt = ft_strdup(str)))
		return (0);
	((t_fd*)tmp->content)->cur = ((t_fd*)tmp->content)->txt;
	((t_fd*)tmp->content)->fd = fd;
	ft_lstadd(fd_lst, tmp);
	return (1);
}

static int		is_eol(char **line, char *buf, t_list **fd_lst, int fd)
{
	char	*str;
	int		ret;

	ret = 0;
	if ((str = ft_strchr(buf, '\n')))
	{
		ret = 1;
		*(str++) = '\0';
		if (!(buf = ft_strjoin(*line, buf)))
			return (-1);
		if (*str == '\0' && *fd_lst)
			if (((t_fd*)((*fd_lst)->content))->fd == fd)
				((t_fd*)((*fd_lst)->content))->fd = -1;
		if (*str != '\0')
			if (!fd_new(str, fd, fd_lst))
				return (-1);
	}
	else if (!(buf = ft_strjoin(*line, buf)))
		return (-1);
	free(*line);
	*line = buf;
	return (ret);
}

static int		check_fd(int fd, t_list **head_lst, char **line)
{
	t_list	*fd_lst;
	t_list	*tmp;
	int		ret;

	fd_lst = *head_lst;
	tmp = NULL;
	while (fd_lst)
	{
		if (((t_fd*)((fd_lst)->content))->fd == fd)
		{
			ret = is_eol(line, ((t_fd*)((fd_lst)->content))->cur, &fd_lst, fd);
			if (!ret || (((t_fd*)((fd_lst)->content))->fd) == -1)
			{
				if (tmp)
					tmp->next = fd_lst->next;
				else
					*head_lst = fd_lst->next;
				ft_lstdelone(fd_lst, del);
			}
			return (ret);
		}
		tmp = fd_lst;
		fd_lst = fd_lst->next;
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*fd_list;
	int				ret;

	if (fd < 0 || !line || !(*line = (char*)malloc(1)))
		return (-1);
	**line = '\0';
	if (!(ret = check_fd(fd, &fd_list, line)))
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			*(buf + ret) = '\0';
			if ((ret = is_eol(line, buf, &fd_list, fd)))
				break ;
		}
	if (!ret && **line != '\0')
		return (2);
	if (ret == 1)
		return (1);
	free(*line);
	*line = NULL;
	if (!ret)
		return (0);
	ft_lstdel(&fd_list, del);
	return (-1);
}
