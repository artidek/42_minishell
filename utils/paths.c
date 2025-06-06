/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:33:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/06/06 12:28:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exist(char *path)
{
	if (access(path, R_OK) == 0 || access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*find_path(char *cmd, char **paths)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		temp = ft_strdup(path);
		free(path);
		path = ft_strjoin(temp, cmd);
		if (check_exist(path))
		{
			free(temp);
			return (path);
		}
		free(temp);
		free(path);
		path = NULL;
		i++;
	}
	if (errno == 2)
		ft_printf("%s: command not found\n", cmd);
	return (path);
}
