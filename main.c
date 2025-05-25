/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:48:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/24 20:59:25 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_builtins(t_main_dat *main_data)
{
	main_data->func_ptr[0] = ft_cd;
	main_data->func_ptr[1] = ft_echo;
	main_data->func_ptr[2] = ft_pwd;
	main_data->func_ptr[3] = ft_export;
	main_data->func_ptr[4] = ft_unset;
	main_data->func_ptr[5] = ft_env;
	main_data->func_ptr[6] = ft_exit;
}

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

int	main(int argc, char **argv, char **envp)
{
	t_main_dat	main_data;

	main_data.pipe = 0;
	main_data.input_data.heredoc_in.line = NULL;
	main_data.input_data.heredoc_in.heredoc_data = NULL;
	main_data.input_data.input = NULL;
	main_data.input_data.prompt = NULL;
	main_data.exit_code = 0;
	main_data.env_cp = NULL;
	main_data.env_cp = initshellenv(main_data.env_cp, envp);
	init_builtins(&main_data);
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
