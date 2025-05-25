/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:33:35 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/25 19:44:39 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

void	trim_arg(char **arg)
{
	int	len;
	char	*temp;

	if (*arg[0] == '\"' || *arg[0] == '\'')
		temp = ft_strdup(*arg + 1);
	else
		temp = ft_strdup(*arg);
	len = ft_strlen(temp);
	if (temp[len - 1] == '\"' || temp[len - 1] == '\'')
	{
		temp[len - 1] = 0;
		free(*arg);
		*arg = ft_strdup(temp);
		free(temp);
		return;
	}
	free(temp);
}

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
	return (path);
}
