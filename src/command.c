#include "hmini.h"

char				getpath(char *cmd, t_env *env)
{
	t_env			*cursor;
	char			fullpath[MAXPATHLEN + 1];

	ft_bzero(fullpath, MAXPATHLEN + 1);
	if (!(cursor = get_env_var("PATH", env)))
		return (NULL);
}

int					builtin_chk(char **tab, char *cmd)
{
	(!(ft_strncmp("cd ", cmd, 3)) ? cd_bin(tab, cmd) : 1;
	(!(ft_strncmp("env ", cmd, 4)) ? env_bin(tab, cmd) : 1;
	(!(ft_strncmp("echo ", cmd, 5)) ? echo_bin(tab, cmd) : 1;
	(!(ft_strncmp("exit ", cmd, 5)) ? exit_bin(tab, cmd) : 1;
	(!(ft_strncmp("setenv ", cmd, 7)) ? senv_bin(tab, cmd) : 1;
	(!(ft_strncmp("unsetenv ", cmd, 9)) ? uenv_bin(tab, cmd) : 1;
}
