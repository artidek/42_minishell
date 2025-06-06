/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:58:26 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:57:17 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	disable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_echoctl(void)
{
	struct termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	cmd_not_found(char *arg)
{
	if (!check_exist(arg))
	{
		ft_printf("%s\n: command not found\n", arg);
		return (1);
	}
	return (0);
}
