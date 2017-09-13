/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 21:35:34 by vboivin           #+#    #+#             */
/*   Updated: 2017/09/13 23:19:47 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static int			getlen_list(t_env *inp)
{
	int				outp;
	
	outp = 0;
	while (inp)
	{
		outp++;
		inp = inp->next;
	}
	return (outp);
}

static char			*getname_env(char *inp)
{
	int				i[2];
	char			*outp;

	i[0] = -1;
	i[1] = 0;
	if (!inp)
		return (NULL);
	while (inp[i[1]] && inp[i[1]] != '=')
		i[1]++;
	if (!(outp = malloc(sizeof(char) * (i[1] + 1))))
		return (NULL);
	while (++i[0] < i[1] && inp[i[0]] && inp[i[0]] != '=')
		outp[i[0]] = inp[i[0]];
	outp[i[0]] = 0;
	return (outp);
}

t_env				*mkenv(char *inp)
{
	t_env			*outp;

	if (!(outp = malloc(sizeof(t_env))))
		return (NULL);
	outp->next = NULL;
	outp->orig = ft_strdup(inp);
	outp->name = getname_env(inp);
	outp->cont = ft_strdup(strrchr(inp, '=') + 1);
	return (outp);
}

t_env				*translate_env(char *env_o[])
{
	t_env			*env;
	t_env			*cursor;
	int				i;

	if (!env_o)
		return(init_env());
	i = 0;
	if(!(env = mkenv(env_o[i])))
		return (NULL);
	cursor = env;
	while (env_o[++i])
	{
		if(!(cursor->next = mkenv(env_o[i])))
			return (NULL);
		cursor = cursor->next;
	}
	printf("he\n");
	return (env);
}

char				**rmk_env(t_env *elist)
{
	char			**outp;
	int				i[2];

	i[0] = -1;
	i[1] = getlen_list(elist);
	if (i[1] && !(outp = malloc((i[1] + 1) *sizeof(char *))))
		return (NULL);
	while (elist)
	{
		outp[++i[0]] = elist->orig;
		elist = elist->next;
	}
	return (outp);
}
