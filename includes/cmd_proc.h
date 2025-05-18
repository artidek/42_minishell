/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_proc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:47:23 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/18 19:58:05 by aobshatk         ###   ########.fr       */
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

typedef struct s_charset
{
	int					*count;
	char				chr;
	struct s_charset	*next;
}						t_charset;

typedef struct s_redir
{
	char				*redir_in;
	char				*redir_out;
}						t_redir;

typedef struct s_args
{
	char				*arg;
	struct s_args		*next;
}						t_args;

typedef struct s_commands
{
	char				*path;
	char				**argv;
	struct s_commands	*next;
}						t_commands;

typedef struct s_seq
{
	int					pipe;
	t_redir				redir_paths;
	t_commands			*commands;
}						t_seq;

void					parse_input(char *input, t_seq **sequence);
void					add_sequence(t_seq **sequence);
void					clear_sequence(t_seq **sequence);
void					clear_charset(t_charset **set);
void					add_charset(t_charset **set, t_charset *new_set);
void					clear_charset(t_charset **set);
void					update_list(t_args **args, char *arg);
void					ext_qt(char **arg, char **res, int *i);
void					del_a(char *argument);
void					add_node_a(t_args **lst, t_args *new);
void					clear_list_a(t_args **lst, void (*del_a)(char *));
void					delete_node_a(t_args *lst, void (*del_a)(char *));
t_charset				*extract_string(char *str, char *delim_set);
t_charset				*new_charset(char c);
t_args					*create_node_a(char *argument);
char					**split_arguments(char *arguments);
char					**create_argv(t_args **args);

#endif
