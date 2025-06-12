/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:20:44 by svolkau           #+#    #+#             */
/*   Updated: 2025/06/09 14:34:46 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

typedef struct s_shenv
{
	char			*key;
	char			*value;
	int				export;
	struct s_shenv	*next;
}					t_shenv;

# include <dirent.h>

void				delone(t_shenv **en, char *key);
t_shenv				*initshellenv(t_shenv *en, char **env);
void				freeenv(t_shenv *en);
int					getposeql(char *str);
void				addback(t_shenv **en, t_shenv *new);
t_shenv				*new(char *key, char *value, int export);
char				*trimall(char *str);
char				*cwd(void);
void				printexport(t_shenv *en);
int					findkey(t_shenv *en, char *key);
int					getposeql(char *str);
void				freeenv(t_shenv *en);

#endif
