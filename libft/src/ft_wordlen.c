/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:12:22 by vboivin           #+#    #+#             */
/*   Updated: 2017/07/26 11:43:33 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_pathlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] > 32 && ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'
		|| (str[i] >= '1' && str[i] <= '9')))
		i++;
	return (i);
}
