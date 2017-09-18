#include "hmini.h"

void				write_prompt(t_env *env)
{
//	char			*prompt;
	t_env			*prompt_var;

	prompt_var = get_env_var("PS1", env);
	ft_putstr(prompt_var->cont);
}
