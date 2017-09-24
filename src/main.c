/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/09/13 23:40:58 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					exec_cli(char *cli, t_env *i_env)
{
	char			fullpath[MAXPATHLEN + 1];
	char			**tab;
	char			**env;
	int				bin;

	if (!cli[0])
		return (0);
	tab = ft_strsplitw(cli);
	bin = builtin_chk(tab, cli, i_env);
	if (!bin && !fork())
	{
		if (!(getpath(tab[0], i_env, fullpath)))
		{
			env = rmk_env(i_env);
			execve(fullpath, tab, env);
		}
	}
	wait(NULL);
	free_rec_char(tab);
	return (0);
}

int					main(int ac, char **av, char **env_o)
{
	char			*cli;
	t_env			*env;

	(void)ac;
	(void)av;
	env = translate_env(env_o, 0);
	write_prompt(env);
	while (get_next_line(0, &cli))
	{
		exec_cli(cli, env);
		write_prompt(env);
		free(cli);
	}
	return (0);
}
