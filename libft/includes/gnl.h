/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:36:22 by kdouveno          #+#    #+#             */
/*   Updated: 2017/12/06 16:39:00 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl
{
	char			c[BUFF_SIZE + 1];
	int				pos;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;

#endif
