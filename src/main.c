/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/31 03:22:45 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static t_env		*g_backup_env;

void				signal_newline(int inp)
{
	(void)inp;
	write(1, "\n", 1);
}

void				signal_handler(int inp)
{
	(void)inp;
	write(1, "\n", 1);
	write_prompt(g_backup_env);
}

int					filter_cli(char **tab, char fp[], char *cli, t_env *i_env)
{
	int				bin;
	int				wit;

	wit = 0;
	if (!cli || !cli[0])
		return (-1);
	while (*cli && *cli <= 32)
		cli++;
	if (!*cli)
		return (-2);
	ft_bzero(fp, MAXPATHLEN * 2 + 1);
	bin = builtin_chk(tab, cli, i_env) ? 1 : 0;
	if (!bin)
		if ((!(ft_strcmp("\\", cli))) || (wit = getpath(tab[0], i_env, fp)) < 0)
		{
			wit == -2 ? 0 :
			pcat("minishell: ", NULL, ": Cannot execute command", 1);
			return (-1);
		}
	if (!fp[0] && !bin)
		derror(tab[0], NULL, NULL, 0);
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
		access(fullpath, X_OK) ?
		pcat("minishell: ", fullpath, ": Permission denied.", 1) :
		pcat("minishell: ", fullpath, NEOB, 1);
		exit(0);
	}
	(!bin && fullpath[0]) ? signal(SIGINT, &signal_newline) : 0;
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
	while (get_next_line(0, &cli) > 0)
	{
		cli = line_env_interpret(cli, env);
		exec_cli(cli, env);
		signal(SIGINT, &signal_handler);
		write_prompt(env);
		cli ? free(cli) : 0;
	}
	ft_putstr("\rEnd of stream.                                            \n");
	return (0);
}
