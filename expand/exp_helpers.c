/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:45:31 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/02 11:45:18 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	get_exp_val(char **str, int *i, t_expand **exp, char *arg)
{
	if (*str)
		update_expand(exp, str, 0);
	n_q_inner(arg, i, exp);
}
