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

static t_env		*backup_env;

void				signal_handler(int inp)
{
	(void)inp;
	write(1, "\n", 1);
	write_prompt(backup_env);
}

void				error_disp(char *cmd)
{
	pcat("minishell: ", cmd, ": ", 0);
	if (ft_strrchr(cmd, '/'))
		ft_putstr("No such file or directory\n");
	else
		ft_putstr("Command not found\n");
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
	getpath(tab[0], i_env, fullpath);
	if (fullpath[0] == 0 && !bin)
		error_disp(tab[0]);
	if (!bin && fullpath[0] && !fork())
	{
		signal(SIGINT, SIG_DFL);
		env = rmk_env(i_env);
		execve(fullpath, tab, env);
		perror(NULL);
	}
	else
		signal(SIGINT, &signal_handler);
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
	backup_env = env;
	write_prompt(env);
	signal(SIGINT, SIG_IGN);
	while (get_next_line(0, &cli))
	{
		exec_cli(cli, env);
		write_prompt(env);
		free(cli);
	}
	write(1, "\n", 1);
	return (0);
}
