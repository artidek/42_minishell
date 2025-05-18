/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:50:10 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 17:41:50 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd_proc.h"
# include "in_proc.h"

typedef struct s_main_dat
{
	int				stop_heredoc;
	char			*oldpwd;
	t_input_data	input_data;
	t_seq			*sequence;
}					t_main_dat;

int					run_input_processor(t_main_dat *main_data);
int					absl(int num);
int					isalldigit(char *str);
int					arr_len(char **arr);
int					comp_arr(char **arr1, char **arr2);
void				run_command_processor(char *input);
void				free_arr(char **arr);
void				heredoc_in(char *input, t_main_dat *main_data);
char				*read_input(t_main_dat *main_data);

#endif
