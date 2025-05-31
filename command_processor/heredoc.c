/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:04:55 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/31 14:30:49 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	handle_sig(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
}

static	void start_heredoc(char *eof, int fd)
{
	char *line;

	seg_init(SIGINT,handle_sig);
	line = NULL;
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
		if (ft_strncmp(eof, line, ft_strlen(line)) == 0 && (ft_strlen(eof) == ft_strlen(line)))
		{
			free(line);
			return;
		}
		free(line);
	}
}

int	heredoc(char *eof)
{
	int	fd;
	int	pid;
	int	status;
	struct sigaction	sa_orig;

	sig_ignore(&sa_orig);
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
	waitpid(pid, &status, 0);
	if(WEXITSTATUS(status) == 1)
		return (fd);
	if (WEXITSTATUS(status) == 2)
		return (2);
	sig_restore(&sa_orig);
	return (1);
}
