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

	tab = ft_strsplitw(cli);
	bin = builtin_chk(tab, i_env);
	printf("waiiiitwat\n");
	if (!bin && !fork())
	{
		printf("wat_\n");
		if (!(getpath(tab[0], i_env, fullpath)))
		{
			printf("wat\n");
			env = rmk_env(i_env);
			printf("wat1\n");
			execve(fullpath, tab, env);
			printf("wat2\n");
			printf("wat3\n");
		}
		printf("wat_2\n");
	}
	if (bin)
		wait(NULL);
	free_rec_char(tab);
	write_prompt(i_env);
	printf("out of exec\n");
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
		printf("exxing\n");
		exec_cli(cli, env);
		free(cli);
	}
	return (0);
}
