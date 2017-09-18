#include "hmini.h"

void				cd_bin(char **tab, t_env *env)
{
	t_env			*cursor[2];

	if (chdir(tab[1]) < 0)
		perror(NULL);
	else
	{
		cursor[0] = get_env_var("PWD", env);
		cursor[1] = get_env_var("OLDPWD", env);
		edit_var_content(cursor[0], tab[1]);
		edit_var_content(cursor[1], cursor[0]->cont);
	}
}
