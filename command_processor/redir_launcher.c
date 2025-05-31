/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_launcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:44:23 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/31 13:48:06 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static int	redir_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		return(0);
	}
	close(fd);
	return (1);
}

static int	redir_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		return(0);
	}
	close(fd);
	return (1);
}

int	redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell");
		return (0);
	}
	close(fd);
	return (1);
}

static int	start_redir(t_redir *redir)
{
	if (redir->redir_type == REDIR_IN)
	{
		if (!redir_in(redir->file))
			return (0);
	}
	if (redir->redir_type == REDIR_OUT)
	{
		if (!redir_out(redir->file))
			return (0);
	}
	if (redir->redir_type == REDIR_APP)
	{
		if (!redir_append(redir->file))
			return (0);
	}
	return (1);
}

int	launch_redir(t_seq *sequence)
{
	t_redir	*redir;

	redir = sequence->redirect;
	if (!redir)
		return (1);
	while (redir)
	{
		if (redir->redir_type != HEREDOC)
		{
			if (!start_redir(redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
