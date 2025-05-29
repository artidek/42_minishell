/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:48:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/29 18:41:54 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_val(t_expand **exp, t_main_dat *main_data)
{
	t_shenv	*env_tmp;

	env_tmp = main_data->env_cp;
	while (env_tmp)
	{
		if (ft_strncmp((*exp)->exp_str, env_tmp->key,
				ft_strlen((*exp)->exp_str)) == 0 && ft_strncmp((*exp)->exp_str,
				env_tmp->key, ft_strlen(env_tmp->key)) == 0)
		{
			free((*exp)->exp_str);
			(*exp)->exp_str = ft_strdup(env_tmp->value);
		}
		env_tmp = env_tmp->next;
	}
}

void	expand(t_expand **exp, t_main_dat *main_data)
{
	t_expand	*temp;

	temp = *exp;
	while (temp)
	{
		if (temp->exp == 1)
			get_val(&temp, main_data);
		temp = temp->next;
	}
}
