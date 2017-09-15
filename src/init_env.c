/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 23:20:15 by vboivin           #+#    #+#             */
/*   Updated: 2017/09/13 23:41:00 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

t_env			*creat_var(char *name, char *cont, char *full, int allc)
{
	t_env		*outp;

	printf("%d\n", allc);
	if ((!name) && full)
		name = get_cut_env(full, 0);
	if ((!cont) && full)
		cont = get_cut_env(full, 1);
	if (!(outp = sizeof(t_env *)))
		return (NULL);
	outp->name = (allc & MONE) ? name : ft_strdup(name);
	outp->cont = (allc & MTWO) ? cont : ft_strdup(cont);
	if (allc & MFOU && !name && !cont)
		outp->full = full;
	else
	{
		outp->full = malloc(ft_strlen(name) + ft_strlen(cont) + 3);
		ft_strcat(outp->full, outp->name);
		ft_strcat(outp->full, "=");
		ft_strcat(outp->full, outp->cont);
	}
	outp->allc = allc;
	outp->next = NULL;
	return (outp);
}

t_env			init_env()
{
	t_env		*env;
	t_env		*cursor;
	char		*temp;

	ft_putstr(N_ENV);
	temp = getcwd(NULL, 0);
	if (!(env = creat_var("PWD", temp, NULL, MTWO)))
		push_error(1);
	if (!(env->next = creat_var("PS1", "\\d_\\u>_", NULL, 0)))
		push_error(1);
	cursor = env->next;
	if (!(cursor->next = creat_var(NULL, NULL, env->full, 
}
