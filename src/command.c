/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:37 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 01:40:20 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*skip_cmd(char *inp, int nb)
{
	inp += nb;
	while (*inp && *inp < 32)
		inp++;
	return (inp);
}

static void			chk_exist(char *cmd, char **path, char *fullpath)
{
	struct stat		statf;
	int				i;

	i = 0;
	ft_bzero(fullpath, MAXPATHLEN + 1);
	ft_strcat(fullpath, path[i++]);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, cmd);
	while (lstat(fullpath, &statf) && path[i])
	{
		ft_bzero(fullpath, MAXPATHLEN + 1);
		ft_strcat(fullpath, path[i++]);
		ft_strcat(fullpath, "/");
		ft_strcat(fullpath, cmd);
	}
	if (!(path[i]) && lstat(fullpath, &statf))
		ft_bzero(fullpath, MAXPATHLEN + 1);
}

int					getpath(char *cmd, t_env *env, char *fullpath)
{
	t_env			*cursor;
	char			**content;
	int				i;
	struct stat		statf;

	ft_bzero(fullpath, MAXPATHLEN + 1);
	if (!lstat(cmd, &statf) && ft_strrchr(cmd, '/') && (i = -1))
	{
		ft_strcpy(fullpath, cmd);
		return (0);
	}
	if (!(cursor = get_env_var("PATH", env)))
	{
		if (lstat(cmd, &statf))
			return (-1);
		ft_strcpy(fullpath, cmd);
		return (0);
	}
	if (!(content = ft_strsplit(cursor->cont, ':')))
		return (-1);
	chk_exist(cmd, content, fullpath);
	while (content[++i])
		free(content[i]);
	free(content);
	return (0);
}

int					builtin_chk(char **tab, char *cmd, t_env *env)
{
	int				wit;

	wit = 6;
	if (!tab[0])
		return (0);
	(!ft_strncmp("exit", tab[0], 5)) ? exit_bin(tab, cmd, env) : wit--;
	(!ft_strncmp("cd", tab[0], 3)) ? cd_bin(tab, env) : --wit;
	(!ft_strncmp("env", tab[0], 4)) ? env_bin(tab, env) : --wit;
	(!ft_strncmp("setenv", tab[0], 7)) ? setenv_bin(tab, cmd, env) : --wit;
	(!ft_strncmp("unsetenv", tab[0], 9)) ? uenv_bin(tab, env) : --wit;
	(!ft_strncmp("echo", tab[0], 5)) ? echo_bin(tab, cmd, env) : --wit;
	return (wit);
}
