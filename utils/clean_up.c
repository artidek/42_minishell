/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:35:30 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/30 16:56:50 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	o_q_s_rem(char **arg)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if ((*arg)[i] == '\"' || (*arg)[i] == '\'')
		i++;
	else
		return;
	while ((*arg)[i])
	{
		if ((*arg)[i] != '\\')
			add_to_str(&str, 1, &(*arg)[i]);
		i++;
	}
	if (i > 0 && ft_strlen(str) > 0)
		str[ft_strlen(str) - 1] = 0;
	free(*arg);
	if (str)
		*arg = ft_strdup(str);
	else
		*arg = ft_strdup("empty");
	printf("arg %s len %ld\n", *arg, ft_strlen(*arg));
}

static void	full_clean(char **arg)
{
	char	*str;
	char	*trimmed;
	int		i;

	i = 0;
	str = NULL;
	trimmed = ft_strtrim(*arg, " ");
	if (trimmed[i] == '\"' || trimmed[i] == '\'')
		i++;
	while (trimmed[i])
	{
		if (trimmed[i] != '\\')
			add_to_str(&str, 1, &trimmed[i]);
		i++;
	}
	if (i > 0)
		str[ft_strlen(str) - 1] = 0;
	free(*arg);
	if (str && *str)
		*arg = ft_strdup(str);
	else
		*arg = ft_strdup("empty");
}

void	clean_up_arg(char ***arg)
{
	int	i;

	i = 0;
	if (ft_strncmp((*arg)[i], "echo", ft_strlen((*arg)[i])) == 0
		&& ft_strncmp((*arg)[i], "echo", ft_strlen("echo")) == 0)
	{
		while ((*arg)[i])
		{
			o_q_s_rem(&(*arg)[i]);
			i++;
		}
	}
	else
	{
		while ((*arg)[i])
		{
			full_clean(&(*arg)[i]);
			i++;
		}
	}
	int j = 0;
	while ((*arg)[j])
	{
		printf("after cup %s\n", (*arg[j]));
		j++;
	}
}
