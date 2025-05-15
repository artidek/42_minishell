/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:50:10 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/15 15:16:38 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define EXIT_PROG 3

int		arr_len(char **arr);
int		process_failed(pid_t pid);
int		create_pipe(int *pipefd);
int		read_pipe(int read_end, char **input);
int		alloc_str(char **str, int size);
int		isalldigit(char *str);
int absl(int num);
char	*init_prompt(void);
int		run_input_processor(void);
void	free_arr(char **arr);
void	seg_init(int signal, void(sig_handler)(int));
void	run_command_processor(char *input);

#endif
