/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:30:27 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:29:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len])
		len++;
	return (len);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

int	alloc_str(char **str, int size)
{
	*str = malloc(sizeof(char) * size + 1);
	if (!(*str))
		return (0);
	return (1);
}

void	seg_init(int signal, void (sig_handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(signal, &sa, NULL);
}

int	absl(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}
