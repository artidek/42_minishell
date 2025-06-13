/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:41:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/13 21:26:20 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	g_sig = 0;

void	wait_and_clear(t_main_dat *main_data)
{
	t_seq	*seq;
	int		status;

	seq = main_data->sequence;
	while (seq)
	{
		waitpid(seq->pid, &status, 0);
		last_command(main_data, seq);
		seq = seq->next;
	}
	WEXITSTATUS(status);
	enable_echoctl();
	clear_command_proc(main_data);
	if (g_sig > 0)
		handle_exit(main_data, g_sig);
	else if (status > 0)
		handle_exit(main_data, 2);
	else
		handle_exit(main_data, 0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		g_sig = 130;
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_sig = 131;
	}
}

static void	run_command(t_main_dat *main_data)
{
	disable_echoctl();
	execve(main_data->sequence->commands->path,
		main_data->sequence->commands->argv, main_data->envp_cp);
}

int	is_builtin(t_main_dat *main_data, t_seq *seq)
{
	int			i;
	int			status;
	t_commands	*commands;

	commands = seq->commands;
	i = built_in(commands->argv[0]);
	last_command(main_data, seq);
	if (i >= 0)
	{
		status = main_data->func_ptr[i](main_data, commands->argv);
		if (status > 0)
		{
			handle_exit(main_data, 2);
			return (2);
		}
		else
			handle_exit(main_data, 0);
		if (!main_data->sequence->next)
			clear_command_proc(main_data);
		return (1);
	}
	return (0);
}

void	single_command(t_main_dat *main_data)
{
	int	pid;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (!launch_redir(main_data->sequence))
	{
		clear_command_proc(main_data);
		return ;
	}
	if (main_data->sequence->commands->argv && !is_builtin(main_data,
			main_data->sequence))
	{
		pid = fork();
		if (process_failed(pid))
		{
			clear_command_proc(main_data);
			return ;
		}
		if (pid == 0)
			run_command(main_data);
		main_data->sequence->pid = pid;
		wait_and_clear(main_data);
	}
}
