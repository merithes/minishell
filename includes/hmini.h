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


void						write_prompt(t_env *env);
int							getpath(char *cmd, t_env *env, char *fullpath);
void						cd_bin(char **tab, t_env *env);

void						edit_var_content(t_env *elem, char *cont);
char						**rmk_env(t_env *inp);

t_env						*translate_env(char *env[], int type);
t_env						*init_env(void);

t_env						*get_env_var(char *to_search, t_env *list);
char						*get_cut_env(char *inp, int type);

#endif
