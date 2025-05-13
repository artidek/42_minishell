/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:05:07 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/13 18:42:02 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_failed(pid_t pid)
{
	if (pid < 0)
	{
		perror("Failed to create process");
		return (1);
	}
	return (0);
}

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) < 0)
	{
		perror("Failed to create pipe");
		return (0);
	}
	printf("%d pipefd1 0\n", pipefd[0]);
	return (1);
}
