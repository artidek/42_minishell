/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_proc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:47:23 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 09:57:27 by aobshatk         ###   ########.fr       */
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
	t_redir				redir_paths;
	int					redir_in_fd;
	int					redir_out_fd;
	t_commands			*commands;
	struct s_seq		*next;
}						t_seq;

void					parse_input(char *input, t_seq **sequence);
void					add_sequence(t_seq **sequence);
void					clear_sequence(t_seq **sequence);
void					clear_charset(t_charset **set);
void					add_charset(t_charset **set, t_charset *new_set);
void					clear_charset(t_charset **set);
void					run_command_processor(char *input);
t_charset				*extract_string(char *str, char *delim_set);
t_charset				*new_charset(char c);

#endif
