/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <vboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 18:20:54 by nmougino          #+#    #+#             */
/*   Updated: 2016/10/20 21:39:25 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_nb_word(const char *s)
{
	size_t	i;
	int		isword;
	int		brackets;

	i = 0;
	isword = 0;
	brackets = 0;
	while (*s)
	{
		while (*s && *s <= 32)
			s++;
		*s ? isword++ : 1;
		while (*s > 32 && *s != '"')
			s++;
		if (*s == '"')
			while (*s && brackets != 2)
			{
				*s == '"' ? brackets++ : 1;
				s++;
			}
	}
	return (i);
}

static size_t	ft_length_word(const char *s)
{
	size_t	length;

	length = 0;
	while (*s && *s > 32 && *s !='"')
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplitw(const char *s)
{
	char	**tab;
	int		i;
	int		wlen;
	size_t	nbword;

	i = 0;
	nbword = ft_nb_word(s);
	tab = (char **)malloc(sizeof(char *) * (nbword + 1));
	if (!tab)
		return (NULL);
	while (nbword--)
	{
		wlen = ft_length_word(s);
		if (!(tab[i] = ft_strnew(wlen)))
			return (NULL);
		s += wlen;
		if (
		while (*s && *s <= 32)
			s++;
			/*
		tab[i] = ft_strsub(s, 0, ft_length_word(s));
		if (!tab[i])
			return (NULL);
		s = s + ft_length_word(s);
		i++;*/
	}
	tab[i] = NULL;
	return (tab);
}
