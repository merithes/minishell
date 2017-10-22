/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:02 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/22 00:26:24 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				env_bin(char **tab, t_env *env)
{
	t_env			*tmp;

	if (!tab || !env)
		return ;
	env = (!env->name) ? env->next : env;
	if (tab[1])
	{
		tmp = get_env_var(tab[1], env);
		if (tmp && tmp->cont)
		{
			ft_putstr(tmp->cont);
			ft_putchar('\n');
		}
	}
	else
		while (env)
		{
			pcat(env->full, 0, 0, 1);
			env = env->next;
		}
}

void				setenv_bin(char **tab, char *cmd, t_env *env)
{
	char			**svar;
	t_env			*var_exists;
	int				nb[2];

	cmd = skip_cmd(cmd, 7);
	nb[0] = 0;
	if (!tab || !tab[0] || !tab[1]
		|| !env || !(ft_strrchr(tab[1], '=') != tab[1]))
		return ;
	if (!(svar = ft_strsplit(cmd, '=')))
		return ;
	nb[0] = 0;
	while (svar && svar[nb[0]])
		nb[0]++;
	(nb[0] == 3) ? svar[1] = ft_var_brackets(svar[1], 1) : NULL;
	nb[1] = !env_is_valid(svar[0], svar[1]) ? 1 : 0;
	if (!(var_exists = get_env_var(svar[0], env)) && nb[0] >= 1 && nb[1])
		new_var(env, ft_strdup(svar[0]), ft_strdup(svar[1]), MONE + MTWO);
	else if (nb[0] >= 1 && nb[1])
		edit_var_content(var_exists, ft_strdup(svar[1]), 1);
	nb[0] = -1;
	while (svar[++nb[0]])
		free(svar[nb[0]]);
	svar ? free(svar) : 0;
}

void				uenv_bin(char **tab, t_env *root)
{
	t_env			*cursor;
	t_env			*tmp;

	if (!root || !tab || !tab[0] || !tab[1])
		return ;
	cursor = root;
	while (cursor->next && ft_strcmp(cursor->next->name, tab[1]))
		cursor = cursor->next;
	if (!cursor->next)
		return ;
	cursor->next->full ? free(cursor->next->full) : 1;
	cursor->next->name ? free(cursor->next->name) : 1;
	cursor->next->cont ? free(cursor->next->cont) : 1;
	tmp = cursor->next;
	cursor->next = cursor->next->next;
	free(tmp);
}
