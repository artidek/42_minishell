/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:48:42 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 11:33:09 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*var_val(char *cont)
{
	char	*eq_ch;

	eq_ch = NULL;
	eq_ch = ft_strrchr(cont, '=');
	if (eq_ch && *(eq_ch + 1))
		return (ft_strdup(eq_ch + 1));
	eq_ch = malloc(sizeof(char));
	eq_ch[0] = 0;
	return (eq_ch);
}

static void	get_var(t_expand **exp, t_main_dat *main_data)
{
	t_list	*env_tmp;
	char	**eq_split;

	env_tmp = main_data->vars;
	while (env_tmp)
	{
		eq_split = ft_split(env_tmp->content, '=');
		if (ft_strncmp((*exp)->exp_str, eq_split[0],
				ft_strlen((*exp)->exp_str)) == 0 && ft_strncmp((*exp)->exp_str,
				eq_split[0], ft_strlen(eq_split[0])) == 0)
		{
			free((*exp)->exp_str);
			(*exp)->exp_str = var_val(env_tmp->content);
			return ;
		}
		free_arr(eq_split);
		env_tmp = env_tmp->next;
	}
	free((*exp)->exp_str);
	(*exp)->exp_str = malloc(sizeof(char));
	(*exp)->exp_str[0] = 0;
}

static int	get_val(t_expand **exp, t_main_dat *main_data)
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
			return (1);
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

int	is_var(char **argv, t_main_dat *main_data)
{
	if (arr_len(argv) == 1)
	{
		if (ft_strrchr(argv[0], '=') && main_data->pipe && argv[0][0] != '\''
			&& argv[0][0] != '\"')
			return (2);
		if (ft_strrchr(argv[0], '=') && !main_data->pipe && argv[0][0] != '\''
			&& argv[0][0] != '\"')
		{
			expandable(&argv[0], main_data);
			ft_lstadd_back(&main_data->vars, ft_lstnew(ft_strdup(argv[0])));
			return (1);
		}
	}
	return (0);
}

void	expand(t_expand **exp, t_main_dat *main_data)
{
	t_expand	*temp;

	temp = *exp;
	while (temp)
	{
		if (temp->exp == 1)
		{
			if (!get_val(&temp, main_data))
				get_var(&temp, main_data);
		}
		temp = temp->next;
	}
}
