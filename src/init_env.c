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

t_env				*creat_var(char *name, char *cont, char *full, int allc)
{
	t_env			*outp;

	if ((!name) && full)
		name = get_cut_env(full, 0);
	if ((!cont) && full)
		cont = get_cut_env(full, 1);
	if (!(outp = malloc(sizeof(t_env *))))
		return (NULL);
	printf("creat_var\n%d\t%d\n", MONE & allc, MTWO & allc);
	outp->name = (allc & MONE) ? name : ft_strdup(name);
	allc & MONE ? printf("NAME\n") : printf("nNAME\n");
	outp->cont = (allc & MTWO) ? cont : ft_strdup(cont);
	allc & MTWO ? printf("CONT\n") : printf("nCONT\n");
	if (allc & MFOU && !name && !cont)
		outp->full = full;
	else
	{
		if (!(outp->full = (char *)malloc(ft_strlen(name) + ft_strlen(cont) + 3)))
			return (NULL);
		printf("full_m\t%p\n", outp->full);
		ft_bzero(outp->full, ft_strlen(name) + ft_strlen(cont) + 3);
		ft_strcat(outp->full, outp->name);
		ft_strcat(outp->full, "=");
		ft_strcat(outp->full, outp->cont);
		printf("full\t%p\t%s\n", outp->full, outp->full);
	}
	outp->next = NULL;
	printf("pwoopsie\n");
	free(outp->full);
	printf("woopsie\n");
	return (outp);
}

t_env				*init_env(void)
{
	t_env			*env;
	t_env			*cursor;
	char			*temp;

	ft_putstr(N_ENV);
	temp = getcwd(NULL, 0);
	if (!(env = creat_var("PWD", temp, NULL, MTWO)))
		ft_push_error(1);
	if (!(env->next = creat_var("PS1", "PS1>_ ", NULL, 0)))
		ft_push_error(1);
	cursor = env->next;
	if (!(cursor->next = creat_var("OLDPWD", NULL, env->full, 0))) 
		ft_push_error(1);
	cursor = cursor->next;
	if (!(cursor->next = creat_var("SHLVL", "1", 0, 0))) 
		ft_push_error(1);
	return (env);
}

t_env				*new_var(t_env *root, char *name, char *cont, int allc)
{
	t_env			*outp;

	printf("creatin %s with ptrs:\t%p\t%p\n", name, name, cont);
	outp = creat_var(name, cont, NULL, allc);
	while (root->next)
		root = root->next;
	root->next = outp;
	return (outp);
}
