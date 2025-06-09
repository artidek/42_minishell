/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_proc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:47:23 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/09 12:59:40 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PROC_H
# define CMD_PROC_H

# include "../libft/ft_printf/libftprintf.h"
# include "../libft/libft.h"
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>
# include <wait.h>

# define HEREDOC 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APP 4

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

typedef struct s_redir
{
	int				redir_type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_seq
{
	int				pid;
	char			*temp_redir;
	char			*temp_cmd;
	t_redir			*redirect;
	t_commands		*commands;
	struct s_seq	*next;
}					t_seq;

int					is_redir(char delim, char *args);
int					process_failed(pid_t pid);
int					create_pipe(int *pipefd);
int					check_exist(char *path);
int					redir_in(char *file);
int					n_pth_bin(t_seq **sequence);
int					stop_quotes(char quote, char *input);
void				clear_redirect(t_redir **redirect);
void				add_redirect(t_redir **redir, t_redir *new_redir);
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
void				add_path(char *path, t_seq **sequence);
void				init_str(char **str, char **array);
void				disable_echoctl(void);
void				enable_echoctl(void);
void				extract_outer_string(char **res, char *arg, int *i,
						t_args **args);
void				update_args(char **res, t_args **args);
void				write_quotes(int write_end, char *input);
void				clean_up_arg(char ***arg);
void				skip_sign(char *str, int *i, char sign);
void				proceed_iterate(char **redir_str, char *str, int *i, int j);
void				redir_str(t_seq **sequence, char *str);
void				join_arg(char **arg, char *str, int *i);
void				build_new_args(char ***arg, t_args *args);
void				add_arg(t_args **args, char **arg);
char				**split_arguments(char *arguments);
char				**create_argv(t_args **args);
char				**first_split(char *input);
t_redir				*new_redir(int type, char *file);
t_args				*create_node_a(char *argument);

#endif
