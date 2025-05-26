/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:41:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/26 14:42:05 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	run_command(t_main_dat *main_data)
{
	signal(SIGINT, SIG_DFL);
	disable_echoctl();
	execve(main_data->sequence->commands->path,
		main_data->sequence->commands->argv, NULL);
}

int	is_builtin(t_main_dat *main_data, t_seq *seq)
{
	int			i;
	t_commands	*commands;

	commands = seq->commands;
	i = built_in(commands->argv[0]);
	if (i >= 0)
	{
		main_data->func_ptr[i](main_data, commands->argv);
		if(!main_data->sequence->next)
			clear_command_proc(main_data);
		return (1);
	}
	return (0);
}

void	single_command(t_main_dat *main_data)
{
	int					pid;
	int					status;
	struct sigaction	sa_orig;

	sig_ignore(&sa_orig);
	if (!launch_redir(main_data->sequence))
	{
		clear_command_proc(main_data);
		return ;
	}
	if (main_data->sequence->commands->argv && !is_builtin(main_data, main_data->sequence))
	{
		pid = fork();
		if (process_failed(pid))
		{
			clear_command_proc(main_data);
			return ;
		}
		if (pid == 0)
			run_command(main_data);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) > 0)
			perror("minishell");
	}
	enable_echoctl();
	sig_restore(&sa_orig);
	clear_command_proc(main_data);
}
