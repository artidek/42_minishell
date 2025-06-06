/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:12:01 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 14:49:19 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_pwd(void)
{
	char	buf[PATH_MAX];
	char	*cwd;
	char	**res;

	cwd = getcwd(buf, PATH_MAX);
	res = ft_split(cwd, '/');
	return (res);
}

char	*build_str(char **str1, char **str2, char *str3)
{
	char	*res;
	char	*temp;

	res = ft_strjoin (*str1, *str2);
	free(*str1);
	free(*str2);
	temp = ft_strdup(res);
	free(res);
	res = ft_strjoin(temp, str3);
	free(temp);
	return (res);
}
