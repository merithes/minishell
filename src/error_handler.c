/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:27:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 01:27:31 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				derror(char *cmd, char *path, char *specs, int status)
{
	int				accessd;
	struct stat		statf;

	cmd ?
	pcat("minishell: ", cmd, ":", 0) :
	pcat("minishell: ", cmd, NULL, 0);
	specs ? ft_putstr(specs) : NULL;
	if (status || path)
	{
		path ? lstat(path, &statf) : 0;
		if (!path || (accessd = access(path, R_OK) != 0))
			ft_putstr(NSFOD);
		else if ((accessd = access(path, X_OK)) != 0)
			write(1, " Permissions denied\n", 19);
		else if (S_ISLNK(statf.st_mode))
			write(1, " Link loop\n", 11);
	}
	else
		write(1, " Cannot execute command\n", 24);
}
