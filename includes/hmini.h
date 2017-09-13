/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:25:52 by vboivin           #+#    #+#             */
/*   Updated: 2017/09/13 23:41:02 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMINI_H
# define HMINI_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <dirent.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include "libft.h"

/*
** DEFINED VALUES
** ==============
*/

# define EXIT 55

/*
** /!\SYSTEM DEPENDANT /!\
** =======================
*/

/*
** MACs
** ====
*/

/*
** ARCH
** ====
*/

/*
** MACROS
** ======
*/

/*
** TYPEDEFS
** ========
*/

typedef struct				s_env
{
	char					*orig;
	char					*name;
	char					*cont;
	struct s_env			*next;
}							t_env;

/*
** DECLARATIONS
** ============
*/

t_env						*translate_env(char *env[]);
char						**rmk_env(t_env *inp);

#endif
