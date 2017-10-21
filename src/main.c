/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 06:27:34 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static t_env		*g_backup_env;

void				signal_handler(int inp)
{
	(void)inp;
	write(0, "\n", 1);
	write_prompt(g_backup_env);
}

void				free_list(t_env *root)
{
	t_env			*cursor;
	t_env			*tmp;

	if (!root)
		return ;
	tmp = NULL;
	cursor = root;
	while (cursor || tmp)
	{
		tmp ? free(tmp) : 0;
		if (!cursor)
			break ;
		cursor->name ? free(cursor->name) : 0;
		cursor->cont ? free(cursor->cont) : 0;
		cursor->full ? free(cursor->full) : 0;
		tmp = cursor;
		cursor = cursor->next;
	}
}

int					exec_cli(char *cli, t_env *i_env)
{
	char			fullpath[MAXPATHLEN + 1];
	char			**tab;
	char			**env;
	int				bin;

	if (!cli[0])
		return (0);
	tab = ft_strsplitw(cli);
	bin = builtin_chk(tab, cli, i_env) ? 1 : 0;
	(!bin) ? getpath(tab[0], i_env, fullpath) :
		ft_bzero(fullpath, MAXPATHLEN + 1);
	(fullpath[0] == 0 && !bin) ? derror(tab[0], tab[1], NULL, 0) : 0;
	(fullpath[0]) ? edit_specific_var(i_env, "_", fullpath) :
					edit_specific_var(i_env, "_", tab[0]);
	if (!bin && fullpath[0] && !fork())
	{
		signal(SIGINT, SIG_DFL);
		env = rmk_env(i_env);
		execve(fullpath, tab, env);
		free(env);
	}
	else if (!bin && fullpath[0])
		signal(SIGINT, SIG_IGN);
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
	if (!(env = translate_env(env_o, 0)))
		return (-1);
	g_backup_env = env;
	write_prompt(env);
	signal(SIGINT, &signal_handler);
	while (get_next_line(0, &cli))
	{
		cli = line_env_interpret(cli, env);
		exec_cli(cli, env);
		signal(SIGINT, &signal_handler);
		write_prompt(env);
		free(cli);
	}
	write(1, "\n", 1);
	return (0);
}
