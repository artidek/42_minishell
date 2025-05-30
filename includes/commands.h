/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:20:44 by svolkau           #+#    #+#             */
/*   Updated: 2025/05/30 21:19:28 by aobshatk         ###   ########.fr       */
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
t_shenv				*new (char *key, char *value, int export);

#endif
