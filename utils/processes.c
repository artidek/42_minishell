/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:05:07 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/31 10:54:19 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_failed(pid_t pid)
{
	if (pid < 0)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) < 0)
	{
		perror("minishell");
		return (0);
	}
	return (1);
}

void	sig_ignore(struct sigaction *sa_orig)
{
	struct sigaction	sa_ignore;

	sigaction(SIGINT, NULL, sa_orig);
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
}

void	sig_restore(struct sigaction *sa_orig)
{
	sigaction(SIGINT, sa_orig, NULL);
}

void	restore_sys_files(int stdin_cp, int stdout_cp)
{
	dup2(stdin_cp, STDIN_FILENO);
	dup2(stdout_cp, STDOUT_FILENO);
	close(stdin_cp);
	close(stdout_cp);
}
