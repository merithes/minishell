#include "hmini.h"

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
		if (path[i])
			ft_strcat(fullpath, path[i++]);
		ft_strcat(fullpath, "/");
		ft_strcat(fullpath, cmd);
	}
	if (!(path[i]))
		ft_bzero(fullpath, MAXPATHLEN + 1);
}

int					getpath(char *cmd, t_env *env, char *fullpath)
{
	t_env			*cursor;
	char			**content;
	int				i;

	i = -1;
	ft_bzero(fullpath, MAXPATHLEN + 1);
	if (!(cursor = get_env_var("PATH", env)))
		return (-1);
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
	(!ft_strncmp("cd ", cmd, 3)) ? cd_bin(tab, cmd, env) : 1;
/*	
	(!ft_strncmp("env ", cmd, 4)) ? env_bin(tab, cmd, env) : 1;
	(!ft_strncmp("echo ", cmd, 5)) ? echo_bin(tab, cmd, env) : 1;
	(!ft_strncmp("exit ", cmd, 5)) ? exit_bin(tab, cmd, env) : 1;
	(!ft_strncmp("setenv ", cmd, 7)) ? senv_bin(tab, cmd, env) : 1;
	(!ft_strncmp("unsetenv ", cmd, 9)) ? uenv_bin(tab, cmd, env) : 1;
*/
	return (1);
}
