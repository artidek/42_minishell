/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:11:51 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	run_sig_handlers(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

static void	exec_command(t_seq *seq, int prev_pipe, int *pipefd)
{
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (seq->next)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	execve(seq->commands->path, seq->commands->argv, NULL);
	exit(1);
}

static void	start_process(t_seq *seq, int *pipefd, int prev_pipe,
		t_main_dat *main_data)
{
	int	pid;

	disable_echoctl();
	pid = fork();
	if (pid == 0)
	{
		if (built_in(seq->commands->argv[0]) != -1)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (seq->next)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(pipefd[0]);
			is_builtin(main_data, seq);
			exit(1);
		}
		exec_command(seq, prev_pipe, pipefd);
	}
	seq->pid = pid;
}

void	start_piping(t_main_dat *main_data)
{
	int		prev_pipe;
	int		pipefd[2];
	t_seq	*seq;

	seq = main_data->sequence;
	prev_pipe = STDIN_FILENO;
	run_sig_handlers();
	while (seq)
	{
		if (seq->next && !create_pipe(pipefd))
			return ;
		if (!launch_redir(seq))
		{
			clear_command_proc(main_data);
			return ;
		}
		if (seq->commands->argv)
			start_process(seq, pipefd, prev_pipe, main_data);
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		close(pipefd[1]);
		prev_pipe = pipefd[0];
		seq = seq->next;
	}
	wait_and_clear(main_data);
}
