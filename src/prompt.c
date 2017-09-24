#include "hmini.h"

void				write_prompt(t_env *env)
{
	t_env			*prompt_var;
	
	prompt_var = get_env_var("PS1", env);
	prompt_var ? ft_putstr(prompt_var->cont) : ft_putstr("default_prompt>_ ");
}
