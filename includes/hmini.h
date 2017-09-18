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

# include <sys/stat.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
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
# define N_ENV "Environment received empty. Creating a new one.\n"
# define MONE 0x001
# define MTWO 0x010
# define MFOU 0x100

/*
** /!\SYSTEM DEPENDANT /!\
** ============================================================================
*/

/*
** MACs
** ============================================================================
*/

/*
** ARCH
** ============================================================================
*/

/*
** MACROS
** ============================================================================
*/

/*
** TYPEDEFS
*/

typedef struct				s_env
{
	char					*full;
	char					*name;
	char					*cont;
	int						allc;
	struct s_env			*next;
}							t_env;

/*
** DECLARATIONS
** ============================================================================
*/

t_env						*translate_env(char *env[], int type);
char						**rmk_env(t_env *inp);
t_env						*init_env(void);
t_env						*get_env_var(char *str, t_env *list);
void						write_prompt(t_env *env);
char						*get_cut_env(char *inp, int type);
int							getpath(char *cmd, t_env *env, char *fullpath);

#endif
