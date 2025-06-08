/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_ctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:58:26 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/07 16:58:25 by aobshatk         ###   ########.fr       */
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

int	cmd_not_found(char *arg, t_main_dat *main_data)
{
	if (!check_exist(arg))
	{
		handle_exit(main_data, 127);
		ft_printf("minishell: ");
		ft_printf("%s: No such file or directory\n", arg);
		return (1);
	}
	return (0);
}
