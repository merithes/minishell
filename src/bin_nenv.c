/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_nenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 06:37:50 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*repath(char *inp, t_env *env)
{
	char			*outp;
	t_env			*cursor;

	if (!inp || !env || !(cursor = get_env_var("HOME", env)))
		return (inp);
	if (!(outp = ft_strnew(ft_strlen(cursor->cont) + ft_strlen(inp))))
		return (inp);
	ft_strncat(outp, cursor->cont, ft_strlen(cursor->cont));
	ft_strncat(outp, inp + 1, ft_strlen(inp) - 1);
	free(inp);
	return (outp);
}

void				cd_bin(char **tab, t_env *env)
{
	t_env			*enviro[3];
	char			*cwd;
	char			*chd;
	t_env			*cursor;

	edit_specific_var(env, "minish_bin_", "(builtin: cd)");
	chd = NULL;
	if (tab[1])
		chd = (ft_strrchr(tab[1], '~') == tab[1]) ?
			repath(tab[1], env) : tab[1];
	else if ((cursor = get_env_var("HOME", env)) != NULL)
		chd = ft_strdup(cursor->cont);
	if (chdir(chd) < 0)
		derror("cd", chd, NULL, 1);
	else
	{
		cwd = getcwd(NULL, 0);
		enviro[2] = get_env_var("PWD", env);
		enviro[0] = enviro[2] ? enviro[2] : new_var(env, "PWD", cwd, 0);
		enviro[2] = get_env_var("OLDPWD", env);
		enviro[1] = enviro[2] ? enviro[2] : new_var(env, "OLDPWD", cwd, 0);
		edit_var_content(enviro[1], enviro[0]->cont, 0);
		edit_var_content(enviro[0], cwd, 0);
	}
}

void				echo_bin(char **tab, char *cmd, t_env *env)
{
	int				i;

	if (!tab || !cmd || !env)
		return ;
	cmd = skip_cmd(cmd, 5);
	edit_specific_var(env, "minish_bin_", "(builtin: echo)");
	while (*cmd)
	{
		i = 0;
		if (*cmd == '\\')
		{
			cmd++;
			if (*cmd == 'n' && ++i)
				write(1, "\n", 1);
			else if (*cmd == 't' && ++i)
				write(1, "\t", 1);
			cmd += i;
		}
		write(1, cmd++, 1);
	}
	write(1, "\n", 1);
}

void				exit_bin(char **tab, char *cmd, t_env *env)
{
	int				i;

	i = 0;
	free_list(env);
	while (tab && tab[i])
		free(tab[i++]);
	tab ? free(tab) : 0;
	cmd ? free(cmd) : 0;
	exit(0);
}
