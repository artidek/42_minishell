/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:37:28 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/14 11:46:24 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	at_exit(char *input)
{
	char	**temp;
	int		arrlen;

	if (!input)
		return (0);
	temp = ft_split(input, ' ');
	arrlen = arr_len(temp);
	if (ft_strncmp(temp[0], "exit", 4) == 0 && ft_strlen(temp[0]) == 4)
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

static char	*read_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

int	run_input_processor(void)
{
	char	*input;
	char	*prompt;

	rl_catch_signals = 0;
	while (1)
	{
		prompt = init_prompt();
		input = read_input(prompt);
		if (!at_exit(input))
		{
			rl_clear_history();
			free(prompt);
			free(input);
			return (0);
		}
		run_command_processor(input);
		if (input)
			free(input);
		if (prompt)
			free(prompt);
	}
	return (0);
}
