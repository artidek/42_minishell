/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:37:47 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/02 14:48:07 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sint(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	exit(130);
}

void	handle_sqt(int sig)
{
	(void)sig;
	write(1, "^\\Quit (core dumped)", 21);
	exit(131);
}
