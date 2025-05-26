/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:04:55 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/26 12:58:23 by aobshatk         ###   ########.fr       */
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
			return;
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
	struct sigaction	sa_orig;

	sig_ignore(&sa_orig);
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
	waitpid(pid, NULL, 0);
	close(fd);
	sig_restore(&sa_orig);
	return (1);
}
