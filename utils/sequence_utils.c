/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:47:14 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:38:11 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	proceed_iterate(char **redir_str, char *str, int *i, int j)
{
	while (str[j])
	{
		if ((str[j] == ' ' || str[j] == '>' || str[j] == '<') && j > 0)
			return ;
		add_to_str(redir_str, 1, &str[j]);
		*i += 1;
		j++;
	}
}

void	add_to_str(char **str_add, int size, char *str)
{
	char	*temp;
	char	*temp_str;

	temp = NULL;
	if (!*str_add)
	{
		*str_add = malloc(sizeof(char) * size + 1);
		ft_strlcpy(*str_add, str, size + 1);
		return ;
	}
	temp = ft_strdup(*str_add);
	free(*str_add);
	temp_str = malloc(sizeof(char) * size + 1);
	ft_strlcpy(temp_str, str, size + 1);
	*str_add = ft_strjoin(temp, temp_str);
	free(temp_str);
	free(temp);
}

void	skip_space(char *str, int *j, int *i)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] != ' ')
			return ;
		*j += 1;
		*i += 1;
		a++;
	}
}
