#include "hmini.h"

void				env_bin(char **tab, t_env *env)
{
	t_env			*tmp;

	if (tab[1])
	{
		tmp = get_env_var(tab[1], env);
		if (tmp && tmp->cont)
		{
			ft_putstr(tmp->cont);
			ft_putchar('\n');
		}
	}
	else
	{
		while (env)
		{
			pcat(env->full, 0, 0, 1);
			env = env->next;
		}
	}
}
