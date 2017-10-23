/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_nenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 07:32:38 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				repath(char **tab, t_env *env, char fp[])
{
	t_env			*cursor;

	if (!tab[1] || ft_strrchr(tab[1], '~'))
	{
		if (!(cursor = get_env_var("HOME", env)))
		{
			ft_putstr("HOME not set.\n");
			return ;
		}
		ft_strcat(fp, cursor->cont);
		if (tab[1] && tab[1][1])
			ft_strcat(fp, tab[1] + 1);
	}
	else if (!ft_strcmp(tab[1], "-"))
	{
		if (!(cursor = get_env_var("OLDPWD", env)))
		{
			ft_putstr("OLDPWD not set.\n");
			return ;
		}
		ft_strncpy(fp, cursor->cont, MPL);
		pcat(fp, NULL, NULL, 1);
	}
	else
		ft_strncpy(fp, tab[1], MAXPATHLEN);
}

void				cd_bin(char **tab, t_env *env)
{
	t_env			*pwd[2];
	t_env			*tmp;
	char			*cwd;
	char			chd[MAXPATHLEN + 1];

	ft_bzero(chd, MPL + 1);
	repath(tab, env, chd);
	if (chdir(chd) < 0)
		derror("cd", chd, NULL, 1);
	else
	{
		cwd = getcwd(NULL, 0);
		tmp = get_env_var("PWD", env);
		pwd[0] = tmp ? tmp : new_var(env, "PWD", cwd, 0);
		tmp = get_env_var("OLDPWD", env);
		pwd[1] = tmp ? tmp : new_var(env, "OLDPWD", cwd, 0);
		edit_var_content(pwd[1], pwd[0]->cont, 1);
		edit_var_content(pwd[0], cwd, 0);
	}
}

void				echo_bin(char **tab, char *cmd, t_env *env)
{
	int				i;

	if (!tab || !cmd || !env)
		return ;
	cmd = skip_cmd(cmd, 5);
	i = 0;
	while (tab[++i])
		ft_putstr(tab[i]);
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
