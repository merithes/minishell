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
	int				len;

	if (to_search && list)
		len = ft_strlen(to_search);
	while (list)
		if (ft_strncmp(to_search, list->name, len))
			list = list->next;
		else
			return (list);
	return (NULL);
}

void				edit_var_content(t_env *elem, char *cont)
{
	int				len;

	if (!cont)
	{
		len = ft_strlen(elem->cont);
		free(elem->cont);
		ft_bzero(strrchr(elem->full, '=') + 1, len);
	}
	(elem->cont) ? free(elem->cont) : 1;
	elem->cont = ft_strdup(cont);
	(elem->full) ? free(elem->full) : 1;
	len = (ft_strlen(elem->name) + ft_strlen(elem->cont) + 2);
	elem->full = malloc(len);
	ft_bzero(elem->full, len);
	ft_strcat(elem->full, elem->name);
	ft_strcat(elem->full, "=");
	ft_strcat(elem->full, elem->cont);
}
