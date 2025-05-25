/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:45:51 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/24 17:48:48 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	ft_exit(t_main_dat *main_data, char **gv)
{
	t_main_dat temp;

	temp = *main_data;
	(void)temp;
	while (gv)
	{
		printf("%s\n", *gv);
		gv++;
	}
	return (1);
}
