/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:37:28 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/17 19:44:38 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_heredoc(char *input, t_main_dat *main_data)
{
	char	**temp;
	char	**comp;

	temp = ft_split(input, '\n');
	comp = main_data->input_data.heredoc_in.heredoc_data;
	if (is_heredoc(input))
	{
		if (comp_arr(temp, comp))
		{
			free_arr(temp);
			return ;
		}
		if (main_data->input_data.heredoc_in.heredoc_data)
		{
			free_arr(main_data->input_data.heredoc_in.heredoc_data);
			main_data->input_data.heredoc_in.heredoc_data = NULL;
		}
		heredoc_in(input, main_data);
	}
	free_arr(temp);
}

static void	clear_data(char *input, t_main_dat *main_data)
{
	if (input)
		free(input);
	if (main_data->input_data.prompt)
		free(main_data->input_data.prompt);
	if (main_data->input_data.heredoc_in.line)
	{
		free(main_data->input_data.heredoc_in.line);
		main_data->input_data.heredoc_in.line = NULL;
	}
}

static int	at_exit(char *input)
{
	char	**temp;
	int		arrlen;

	if (!input)
		return (0);
	temp = ft_split(input, ' ');
	arrlen = arr_len(temp);
	if (*temp && ft_strncmp(temp[0], "exit", 4) == 0 && ft_strlen(temp[0]) == 4)
	{
		if (arrlen > 1 && arrlen < 3)
		{
			if (!isalldigit(temp[1]))
				ft_printf("minishell: exit: %s: numeric argument required\n",
					temp[1]);
			else
				write(STDOUT_FILENO, "exit\n", 5);
		}
		if (arrlen > 2)
			ft_printf("minishell: exit: too many arguments\n");
		free_arr(temp);
		if (arrlen == 1)
			write(STDOUT_FILENO, "exit\n", 5);
		return (0);
	}
	free_arr(temp);
	return (1);
}

char	*read_input(t_main_dat *main_data)
{
	char	*input;

	input = readline(main_data->input_data.prompt);
	return (input);
}

int	run_input_processor(t_main_dat *main_data)
{
	char	*input;

	rl_catch_signals = 0;
	while (1)
	{
		main_data->input_data.prompt = init_prompt();
		input = read_input(main_data);
		if (!at_exit(input) || !input)
		{
			rl_clear_history();
			free(main_data->input_data.prompt);
			free(input);
			if (main_data->input_data.heredoc_in.heredoc_data)
				free_arr(main_data->input_data.heredoc_in.heredoc_data);
			return (0);
		}
		check_heredoc(input, main_data);
		if (input && *input && !main_data->input_data.heredoc_in.line)
			add_history(input);
		// run_command_processor(input);
		clear_data(input, main_data);
	}
	return (0);
}
