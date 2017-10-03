#include "hmini.h"

void				cd_bin(char **tab, t_env *env)
{
	t_env			*pwd[2];
	t_env			*tmp;
	struct stat		statf;
	char			*cwd;

	edit_specific_var(env, "minish_bin_", "(builtin: cd)");
	if (chdir(tab[1]) < 0)
	{
		if (!tab[1] || lstat(tab[1], &statf))
			ft_putstr("Cannot change directory: Wrong path\n");
		else if (ft_strlen(tab[1]) > MAXPATHLEN)
			ft_putstr("Cannot change directory: Path too long\n");
		else
			ft_putstr("Cannot change directory: Symbolic links loop\n");
	}
	else
	{
		cwd = getcwd(NULL, 0);
		tmp = get_env_var("PWD", env);
		pwd[0] = tmp ? tmp : new_var(env, "PWD", cwd, 0);
		tmp = get_env_var("OLDPWD", env);
		pwd[1] = tmp ? tmp : new_var(env, "OLDPWD", cwd, 0);
		edit_var_content(pwd[1], pwd[0]->cont);
		edit_var_content(pwd[0], cwd);
	}
}

static size_t		echo_env(char *inp, t_env *root)
{
	size_t			i;
	int				i_cpy;
	char			*tmp;
	t_env			*cursor;

	if (!inp || !root)
		return (0);
	i = 0;
	while (inp[++i] > 32);
	if (!(tmp = ft_strnew(i)))
		return (i);
	inp++;
	i_cpy = -1;
	while (inp[++i_cpy] > 32)
		tmp[i_cpy] = inp[i_cpy];
	if (!(cursor = get_env_var(tmp, root)))
		return ((free(tmp), i));
	ft_putstr(cursor->cont);
	free(tmp);
	return (i);
}

static size_t		echo_spc(char *inp)
{
	int				i;

	if (!inp)
		return (0);
	i = 1;
	if (*inp == 'n' && ++i)
		write(1, "\n", 1);
	else if (*inp == 'r' && ++i)
		write(1, "\r", 1);
	else if (*inp == 't' && ++i)
		write(1, "\t", 1);
	return (i);
}

void				echo_bin(char **tab, char *cmd, t_env *env)
{
	if (!tab || !cmd || !env)
		return ;
	cmd = skip_cmd(cmd, 5);
	edit_specific_var(env, "minish_bin_", "(builtin: echo)");
	while (*cmd)
	{
		cmd += (*cmd == '$') ? echo_env(cmd, env) : 0;
		cmd += (*cmd == '\\') ? echo_spc(cmd + 1) : 0;
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
