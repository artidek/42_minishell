/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_proc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:44:11 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 19:19:29 by aobshatk         ###   ########.fr       */
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

typedef struct s_heredoc_in
{
	int				pipe;
	int				*stop_heredoc;
	char			*line;
	char			**heredoc_data;
}					t_heredoc_in;

typedef struct s_input_data
{
	t_heredoc_in	heredoc_in;
	char			*prompt;
	char			*input;
}					t_input_data;

int					alloc_str(char **str, int size);
int					is_heredoc(char *input);
char				*init_prompt(void);
void				seg_init(int signal, void(sig_handler)(int));

#endif
