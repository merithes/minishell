/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 19:39:55 by vboivin           #+#    #+#             */
/*   Updated: 2016/12/11 18:39:15 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, int qty)
{
	int		j;
	char	*s2;

	if (!(s2 = malloc(sizeof(char) * (qty + 1))))
		return (NULL);
	ft_bzero(s2, qty);
	j = -1;
	while (++j < qty)
		s2[j] = s1[j];
	s2[j] = '\0';
	return (s2);
}
