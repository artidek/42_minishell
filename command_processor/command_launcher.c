/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:41:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/25 21:00:29 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	handle_sig(int signal)
{
	(void)signal;
	//write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

static void	run_command(t_main_dat *main_data)
{
	seg_init(SIGINT, handle_sig);
	execve(main_data->sequence->commands->path, main_data->sequence->commands->argv, NULL);
}

static int	is_builtin(t_main_dat *main_data)
{
	int	i;
	t_commands *commands;

	commands = main_data->sequence->commands;
	i = built_in( commands->argv[0]);
	if (i >= 0)
	{
			main_data->func_ptr[i](main_data, commands->argv);
			clear_command_proc(main_data);
			return (1);
	}
	return (0);
}

void	single_command (t_main_dat *main_data)
{
	int	pid;
	int	status;
	struct sigaction	sa_orig;

	sig_ignore(&sa_orig);
	if (!launch_redir(main_data->sequence))
	{
		clear_command_proc(main_data);
		return ;
	}
	if (!is_builtin(main_data))
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
	sig_restore(&sa_orig);
	clear_command_proc(main_data);
}
