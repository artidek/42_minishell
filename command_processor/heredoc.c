/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:04:55 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:16:35 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_sig(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	exit(254);
}

static void	start_heredoc(char *eof, int fd)
{
	char	*line;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, sigquit_handler);
	line = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		line = readline(">");
		if (line && ft_strncmp(eof, line, ft_strlen(line)) != 0)
		{
			add_to_str(&line, 1, "\n");
			write(fd, line, ft_strlen(line));
		}
		if (!line)
			exit(2);
		if (ft_strncmp(eof, line, ft_strlen(line)) == 0
			&& (ft_strlen(eof) == ft_strlen(line)))
		{
			free(line);
			return ;
		}
		free(line);
	}
}

int	heredoc(char *eof, int *status)
{
	int				fd;
	int				pid;
	struct termios	orig_term;

	tcgetattr(STDIN_FILENO, &orig_term);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	unlink("heredoc");
	fd = open("heredoc", O_RDWR | O_CREAT | O_APPEND, 0644);
	pid = fork();
	if (process_failed(pid))
		return (0);
	if (pid == 0)
	{
		start_heredoc(eof, fd);
		close(fd);
		exit(0);
	}
	waitpid(pid, status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
	if (WEXITSTATUS(*status) == 254)
		return (fd);
	if (WEXITSTATUS(*status) == 2)
		return (2);
	return (fd);
}
