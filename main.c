/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:48:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/23 14:34:39 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	rl_redisplay();
}

int	main(int argc, char **argv)
{
	t_main_dat	main_data;

	main_data.pipe = 0;
	main_data.input_data.heredoc_in.line = NULL;
	main_data.input_data.heredoc_in.heredoc_data = NULL;
	main_data.input_data.input = NULL;
	main_data.input_data.prompt = NULL;
	main_data.exit_code = 0;
	(void)argv;
	if (argc > 1)
	{
		ft_printf("Program doesn't accept arguments\n");
		return (1);
	}
	seg_init(SIGINT, sigint_handler);
	seg_init(SIGQUIT, sigquit_handler);
	run_input_processor(&main_data);
	return (0);
}
