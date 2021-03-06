/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:36:04 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:10:35 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int len;

	if (s == NULL || *s == '\0' || f == NULL)
		return ;
	len = ft_strlen(s) - 1;
	while (len >= 0)
	{
		f(&(s[len]));
		len--;
	}
}
