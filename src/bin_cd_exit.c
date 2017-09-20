#include "hmini.h"

void				cd_bin(char **tab, t_env *env)
{
	t_env			*c_pwd;
	t_env			*o_pwd;
	t_env			*tmp;
	char			*cwd;
	
	if (chdir(tab[1]) < 0)
		perror(NULL);
	else
	{
		cwd = getcwd(NULL, 0);
//		printf("gere\n");
		tmp = get_env_var("PWD", env);
		c_pwd = tmp ? tmp : new_var(env, "PWD", cwd, 0);
		tmp = get_env_var("OLDPWD", env);
//		printf("gere1\n");
		o_pwd = tmp ? tmp : new_var(env, "OLDPWD", cwd, 0);
//		printf("gere2\n");
//		printf("gere3\n");
		edit_var_content(o_pwd, c_pwd->cont);
//		printf("gere4\n");
		edit_var_content(c_pwd, cwd);
		cwd ? free(cwd) : 1;
//		printf("gere5\n");
	}
}
