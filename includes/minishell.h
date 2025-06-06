/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:50:10 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/05 12:58:05 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "cmd_proc.h"
# include "commands.h"
# include "in_proc.h"
# include <linux/limits.h>

typedef struct s_main_dat
{
	int				line_counter;
	int				stdin_cp;
	int				stdout_cp;
	int				pipe;
	int				(*func_ptr[7])(struct s_main_dat *, char **);
	t_list			*vars;
	t_shenv			*env_cp;
	t_input_data	input_data;
	t_seq			*sequence;
}					t_main_dat;

int					run_input_processor(t_main_dat *main_data);
int					absl(int num);
int					isalldigit(char *str);
int					arr_len(char **arr);
int					comp_arr(char **arr1, char **arr2);
int					check_valid(char **args);
int					ft_cd(t_main_dat *main_data, char **gv);
int					ft_pwd(t_main_dat *main_data, char **gv);
int					ft_echo(t_main_dat *main_data, char **gv);
int					ft_env(t_main_dat *main_data, char **gv);
int					ft_export(t_main_dat *main_data, char **gv);
int					ft_exit(t_main_dat *main_data, char **gv);
int					ft_unset(t_main_dat *main_data, char **gv);
int					fill_commands(t_main_dat *main_data, char **paths);
int					built_in(char *arg);
int					is_builtin(t_main_dat *main_data, t_seq *seq);
int					launch_redir(t_seq *sequence);
int					heredoc(char *eof, int *status);
int					fill_redir(t_main_dat *main_data);
int					launch_heredocs(t_seq *seq, t_main_dat *main_data);
int					is_var(char **argv, t_main_dat *main_data);
void				clear_command_proc(t_main_dat *main_data);
void				run_command_processor(t_main_dat *main_data);
void				free_arr(char **arr);
void				init_sequence(t_main_dat *main_data, char **in_arr);
void				sig_ignore(struct sigaction *sa_orig);
void				sig_restore(struct sigaction *sa_orig);
void				restore_sys_files(int stdin_cp, int stdout_cp);
void				single_command(t_main_dat *main_data);
void				expandable(char **arg, t_main_dat *main_data);
void				start_piping(t_main_dat *main_data);
void				check_double_quote(char **arg, t_main_dat *main_data);
void				check_single_quote(char **arg, t_main_dat *main_data);
void				expand(t_expand **exp, t_main_dat *main_data);
void				expandable(char **arg, t_main_dat *main_data);
void				clear_all(t_main_dat *main_data);
void				del(void *var);
void				sighandler(int sig);
void				wait_and_clear(t_main_dat *main_data);
void				handle_exit(t_main_dat *main_data, int status);
void				sigint_handler(int sig);
void				sigquit_handler(int sig);
char				*build_str(char **str1, char **str2, char *str3);
char				**get_pwd(void);

#endif
