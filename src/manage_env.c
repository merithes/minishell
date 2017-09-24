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
	{
		if (ft_strcmp(to_search, list->name))
			list = list->next;
		else
			return (list);
	}
	return (NULL);
}

int					edit_var_content(t_env *elem, char *cont)
{
	int				len;

	if (!elem)
		return (-1);
	len = cont ? ft_strlen(cont) : 0;
	len += elem->name ? ft_strlen(elem->name) : 0;
	printf("I'll be freeing full of %s\t%p\n", elem->name, elem->full);
	elem->full ? free(elem->full) : 1;
	printf("wate\n");
	if (!(elem->full = malloc(len + 2)))
		return (-1);
	elem->cont = cont;
	(elem->full) ? ft_bzero(elem->full, len + 2) : 0;
	(elem->full && elem->name) ? ft_strcat(elem->full, elem->name) : 0;
	(elem->full) ? ft_strncat(elem->full, "=", 1) : 0;
	(elem->full && elem->cont) ? ft_strcat(elem->full, elem->cont) : 0;
	return (0);
}

int					env_is_valid(char *name, char *cont)
{
	int				i;

	i = -1;
	if ((!name || !cont)
		|| ((name[0] < 'A' || name[0] > 'Z') && name[0] != '_'))
			return (-1);
	while (name[++i])
		if ((name[i] < 'A' || name[i] > 'Z') && name[i] != '_'
				&& (name[i] < '0' || name[i] > '9'))
			return (-1);
	i = -1;
	while (cont[++i])
		if (cont[i] == '=')
			return (-1);
	return (0);
}

char				*ft_var_brackets(char *str, int allc)
{
	int				i[2];
	char			*tmp;

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]])
		(str[i[0]] == '"') ? i[1]++ : 1;
	if (i[1] && i[1] != 2)
	{
		allc ? free(str) : 1;
		return (NULL);
	}
	else if (i[1] == 2)
	{
		if (str[0] != '"' || str[ft_strlen(str) - 1] != '"')
			return allc ? (free(str), NULL) : NULL;
		else
		{
			i[1] = (int)ft_strlen(str);
			tmp = (ft_strndup(str + 1, (int)(ft_strlen(str) - 2)));
			return allc ? (free(str), tmp) : tmp;
		}
	}
	return (str);
}
