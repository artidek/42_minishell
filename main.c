/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:48:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/13 16:16:53 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_list	*init_vars(void)
{
	char	*str;
	char	*str1;
	char	*num_to_str;
	t_list	*first_entry;
	t_list	*second_entry;

	str = NULL;
	str1 = NULL;
	num_to_str = ft_itoa(0);
	add_to_str(&str, ft_strlen("?="), "?=");
	add_to_str(&str, ft_strlen(num_to_str), num_to_str);
	free(num_to_str);
	first_entry = ft_lstnew(ft_strdup(str));
	add_to_str(&str1, ft_strlen("0=minishell"), "0=minishell");
	second_entry = ft_lstnew(ft_strdup(str1));
	first_entry->next = second_entry;
	free(str);
	free(str1);
	return (first_entry);
}

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

	main_data.line_counter = 0;
	main_data.pipe = 0;
	main_data.input_data.input = NULL;
	main_data.input_data.prompt = NULL;
	main_data.env_cp = NULL;
	main_data.env_cp = initshellenv(main_data.env_cp, envp);
	main_data.vars = init_vars();
	main_data.sequence = NULL;
	main_data.envp_cp = envp;
	init_builtins(&main_data);
	(void)argv;
	if (argc > 1)
	{
		ft_printf("Program doesn't accept arguments\n");
		return (1);
	}
	run_input_processor(&main_data);
	return (0);
}
