/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_proc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:47:23 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/21 19:37:06 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PROC_H
# define CMD_PROC_H

# include "../libft/ft_printf/libftprintf.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <wait.h>

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_commands
{
	char			*path;
	char			**argv;
}					t_commands;
typedef struct s_seq
{
	char			*temp_redir;
	char			*temp_cmd;
	t_list			*heredoc;
	t_list			*redir_out;
	t_list			*redir_append;
	t_list			*redir_in;
	t_commands		commands;
	struct s_seq	*next;
}					t_seq;

int					is_redir(char delim, char *args);
void				skip_space(char *str, int *j, int *i);
void				add_to_str(char **str_add, int size, char *str);
void				add_sequence(t_seq **sequence);
void				clear_sequence(t_seq **sequence);
void				update_list(t_args **args, char *arg);
void				ext_qt(char **arg, char **res, int *i);
void				del_a(char *argument);
void				add_node_a(t_args **lst, t_args *new);
void				clear_list_a(t_args **lst, void (*del_a)(char *));
void				delete_node_a(t_args *lst, void (*del_a)(char *));
t_args				*create_node_a(char *argument);
char				**split_arguments(char *arguments);
char				**create_argv(t_args **args);

#endif
