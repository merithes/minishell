#include "hmini.h"

char				*get_cut_env(char *inp, int type)
{
	char			*outp;
	int				len;

	if (!inp)
		return (NULL);
	len = (type) ?	(int)ft_strlen(ft_strrchr(inp, '=') + 1) :
					(int)(inp - ft_strrchr(inp, '='));
	if (!(outp = malloc(len + 1)))
		return (NULL);
	outp = (type) ? ft_strdup(ft_strrchr(inp, '=') + 1) :
					ft_strndup(inp, len);
	return (outp);
}

t_env				*get_env_var(char *to_search, t_env *list)
{
	while (list)
		if (ft_strcmp(to_search, list->name))
			list = list->next;
		else
			return (list);
	return (NULL);
}

int					edit_var_content(t_env *elem, char *cont)
{
	int				len;

//	printf("wtf\n");
	if (!elem)
		return (-1);
	len = cont ? ft_strlen(cont) : 0;
	len += elem->name ? ft_strlen(elem->name) : 0;
//	printf("wtf\n");
	if (!(elem->full = malloc(len + 2)))
		return (-1);
//	printf("wtf\n");
	elem->cont = cont;
	elem->full ? free(elem->full) : 1;
	(elem->full) ? ft_bzero(elem->full, len + 2) : 0;
	(elem->full && elem->name) ? ft_strcat(elem->full, elem->name) : 0;
	(elem->full) ? ft_strncat(elem->full, "=", 1) : 0;
	(elem->full && elem->cont) ? ft_strcat(elem->full, elem->cont) : 0;
//	printf("wtf\n");
	return (0);
}
