/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_proc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:44:11 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:48:56 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IN_PROC_H
# define IN_PROC_H

# define _POSIX_C_SOURCE 200809L
//# define _POSIX_C_SOURCE 200112L
# include "../libft/ft_printf/libftprintf.h"
# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

# ifndef HSTNM
#  define HSTNM "hostname"
# endif

typedef struct s_expand
{
	int				exp;
	char			*exp_str;
	struct s_expand	*next;
}					t_expand;

typedef struct s_input_data
{
	char			*prompt;
	char			*input;
}					t_input_data;

int					alloc_str(char **str, int size);
int					is_heredoc(char *input);
int					dollar_check(char *arg, t_expand **exp, char **str, int j);
char				*init_prompt(void);
void				add_expand(t_expand **exp, t_expand *new_exp);
void				clear_expand(t_expand **exp);
void				skip_sp(char **str, char *arg, int *i);
void				update_expand(t_expand **exp, char **str, int ex);
void				join_expanded(char **arg, t_expand *exp);
void				seg_init(int signal, void (sig_handler)(int));
void				s_q_expand(char *arg, t_expand **exp, int *i);
void				upd_str(t_expand **exp, char **str);
t_expand			*new_expand(char *exp_str, int exp);

#endif
