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
		while (env)
		{
			pcat(env->full, 0, 0, 1);
			env = env->next;
		}
}

static char			*skip_cmd(char *inp, int nb)
{
	inp += nb;
	while (*inp && *inp < 32)
		inp++;
	return (inp);
}

void				setenv_bin(char **tab, char *cmd, t_env *env)
{
	char			**svar;
	t_env			*var_exists;
	int				i;
	int				valid;

	cmd = skip_cmd(cmd, 7);
	if (ft_strrchr(tab[1], '=') != tab[1])
		svar = ft_strsplit(cmd, '=');
	else
		return ;
	i = -1;
	while (svar[++i]);
	printf("1\t%s\t%s\n", svar[0], svar[1]);
	(i == 2) ? svar[1] = ft_var_brackets(svar[1], 1) : NULL;
	printf("2\t%s\t%s\n", svar[0], svar[1]);
	valid = !env_is_valid(svar[0], svar[1]) ? 1 : 0;
	if (!(var_exists = get_env_var(svar[0], env)) && i == 2 && valid)
		new_var(env, ft_strdup(svar[0]), ft_strdup(svar[1]), MONE + MTWO);
	else if (i == 2 && valid)
		edit_var_content(var_exists, ft_strdup(svar[1]));
	i = -1;
	while (svar[++i])
		(printf("truc%d\t%p\t%s\n", i, svar[i], svar[i]), free(svar[i]));
	free(svar);
}
