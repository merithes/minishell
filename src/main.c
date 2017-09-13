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
	pid_t			pid;
	char			**tab;
	char			**env;

	(void)env;
	tab = ft_strsplitw(cli);
	pid = fork();
	env = rmk_env(i_env);
	if (pid == 0)
		execve(tab[0], tab, env);
	wait(NULL);
	free_rec_char(tab);
	ft_putstr("$> ");
	(env) ? free(env) : 1;
	return (0);
}

int					main(int ac, char *av[], char *env_o[])
{
	char			*cli;
	t_env			*env;

	(void)ac;
	(void)av;
	env = translate_env(env_o);
	pcat(get_env_var(PS1));
	while (get_next_line(0, &cli))
	{
		exec_cli(cli, env);
		free(cli);
	}
	return (0);
}
