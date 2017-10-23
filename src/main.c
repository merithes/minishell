/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 13:02:35 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static t_env		*g_backup_env;

void				signal_newline(int inp)
{
	(void)inp;
	write(0, "\n", 1);
}

void				signal_handler(int inp)
{
	(void)inp;
	write(0, "\n", 1);
	write_prompt(g_backup_env);
}

int					filter_cli(char **tab, char fp[], char *cli, t_env *i_env)
{
	int				bin;
	int				wit;

	if (!cli || !cli[0])
		return (-1);
	while (*cli && *cli <= 32)
		cli++;
	if (!*cli)
		return (-2);
	ft_bzero(fp, MAXPATHLEN * 2 + 1);
	bin = builtin_chk(tab, cli, i_env) ? 1 : 0;
	if (!bin)
		if ((wit = getpath(tab[0], i_env, fp)) < 0)
		{
			wit == -2 ? 0 :
			pcat("minishell: ", tab[0], ": Cannot execute command", 1);
			return (-1);
		}
	if (!fp[0] && !bin)
		derror(tab[0], tab[1], NULL, 0);
	else if (fp[0] && !bin)
		edit_specific_var(i_env, "_", fp);
	return (bin);
}

void				exec_cli(char *cli, t_env *i_env)
{
	char			fullpath[MAXPATHLEN * 2 + 1];
	char			**tab;
	char			**env;
	int				bin;

	if (!(tab = splitter(cli)))
		return ;
	if ((bin = filter_cli(tab, fullpath, cli, i_env)) < 0)
	{
		free_rec_char(tab);
		return ;
	}
	if (!bin && fullpath[0] && !fork())
	{
		signal(SIGINT, SIG_DFL);
		env = rmk_env(i_env);
		execve(fullpath, tab, env);
		pcat("minishell: ", fullpath, ": Permission denied.", 1);
		exit(0);
	}
	else if (!bin && fullpath[0])
		signal(SIGINT, &signal_newline);
	wait(NULL);
	free_rec_char(tab);
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
