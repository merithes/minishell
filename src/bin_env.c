/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:02 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 01:30:12 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				env_bin(char **tab, t_env *env)
{
	t_env			*tmp;

	if (!tab || !env)
		return ;
	env = (!env->name) ? env->next : env;
	edit_specific_var(env, "minish_bin_", "(builtin: env)");
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
	int				i;
	int				valid;

	edit_specific_var(env, "minish_bin_", "(builtin: setenv)");
	cmd = skip_cmd(cmd, 7);
	if (!tab || !tab[0] || !tab[1]
		|| !env || !(ft_strrchr(tab[1], '=') != tab[1]))
		return ;
	svar = ft_strsplit(cmd, '=');
	i = -1;
	while (svar[i])
		i++;
	(i == 2) ? svar[1] = ft_var_brackets(svar[1], 1) : NULL;
	valid = !env_is_valid(svar[0], svar[1]) ? 1 : 0;
	if (!(var_exists = get_env_var(svar[0], env)) && i == 2 && valid)
		new_var(env, ft_strdup(svar[0]), ft_strdup(svar[1]), MONE + MTWO);
	else if (i == 2 && valid)
		edit_var_content(var_exists, ft_strdup(svar[1]));
	i = -1;
	while (svar[++i])
		free(svar[i]);
	free(svar);
}

void				uenv_bin(char **tab, t_env *root)
{
	t_env			*cursor;
	t_env			*tmp;

	edit_specific_var(root, "minish_bin_", "(builtin: unsetenv)");
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
