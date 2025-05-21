/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:46:50 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/21 12:32:34 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void	test_arguments(char **cmd_argv)
// {
// 	int	i;

// 	i = 0;
// 	while(cmd_argv[i])
// 	{
// 		printf("%s\n", cmd_argv[i]);
// 		i++;
// 	}
// }

static void	extract_seq_it(char **spl_in, t_main_dat *main_data)
{
	init_sequence(main_data, spl_in);
}

void	run_command_processor(t_main_dat *main_data)
{
	char	**spl_in;

	if (!*(main_data->input_data.input))
		return;
	spl_in = ft_split(main_data->input_data.input, '|');
	// if (arr_len(spl_in) > 1)
	// 	main_data->pipe = 1;
	// if (!check_valid(spl_in))
	// {
	// 	free_arr(spl_in);
	// 	return;
	// }
	extract_seq_it(spl_in, main_data);
}
