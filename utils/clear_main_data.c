/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_main_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:04:53 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/01 13:16:50 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../includes/minishell.h"

void	del(void *var)
{
	char *free_var;

	free_var = (char *)var;
	if (free_var)
		free(free_var);
}

void	clear_all(t_main_dat *main_data)
{
	if (main_data->env_cp)
		freeenv(main_data->env_cp);
	if (main_data->input_data.input)
		free(main_data->input_data.input);
	if (main_data->input_data.prompt)
		free(main_data->input_data.prompt);
	if (main_data->vars)
		ft_lstclear(&main_data->vars, del);
	if (main_data->sequence)
		clear_sequence(&main_data->sequence);
}
