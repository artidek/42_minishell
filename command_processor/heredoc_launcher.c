/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:05:49 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/08 19:12:29 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_warning(t_main_dat *main_data, char *eof)
{
	int		fd;
	int		r_line;
	char	line[2];

	fd = open("heredoc", O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_memset(line, 0, 2);
	r_line = read(fd, line, 1);
	main_data->line_counter += 1;
	while (r_line > 0)
	{
		if (line[0] && line[0] == '\n')
			main_data->line_counter += 1;
		r_line = read(fd, line, 1);
	}
	ft_printf("minishell: warning: here-document at line ");
	ft_printf("%d ", main_data->line_counter);
	ft_printf("delimited by end-of-file (wanted `%s')\n", eof);
}

static void	clear_main(t_main_dat *main_data, int fd)
{
	(void)fd;
	close(fd);
	restore_sys_files(main_data->stdin_cp, main_data->stdout_cp);
	unlink("heredoc");
	clear_sequence(&(main_data->sequence));
	main_data->sequence = NULL;
}

int	launch_heredocs(t_seq *seq, t_main_dat *main_data)
{
	int		fd;
	int		status;
	t_redir	*redir;

	redir = seq->redirect;
	while (redir)
	{
		if (redir->redir_type == HEREDOC)
		{
			fd = heredoc(redir->file, &status);
			status = WEXITSTATUS(status);
			if (status == 254)
			{
				clear_main(main_data, fd);
				return (0);
			}
			else if (status == 2)
				heredoc_warning(main_data, redir->file);
		}
		redir = redir->next;
	}
	return (1);
}
