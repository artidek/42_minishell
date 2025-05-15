/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:32:29 by aobshatk          #+#    #+#             */
/*   Updated: 2025/05/15 16:17:18 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_wd(char **pwd, int arrlen)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	printf ("arr_len %d\n", arrlen);
	if (arrlen > 1)
	{
		str1 = ft_strjoin("~", "/");
		str2 = ft_strjoin(str1, pwd[arrlen - 2]);
		free(str1);
		str1 = ft_strjoin(str2, "/");
		free(str2);
		str2 = ft_strjoin(str1, pwd[arrlen - 1]);
		free(str1);
		str1 = ft_strjoin(str2, "$ ");
		free(str2);
		return (str1);
	}
	if (arrlen == 1)
	{
		str1 = ft_strjoin("~", "/");
		str2 = ft_strjoin(str1, pwd[arrlen - 1]);
		free(str1);
	}
	return (str2);
}

static char	*get_name(char *logname, char *hostname)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(logname, hostname);
	res = ft_strjoin(temp, ":");
	free(temp);
	return (res);
}

static char	*build_prompt(char *logname, char *hostname, char **pwd, char **home)
{
	char	*temp1;
	char	*temp2;
	char	*prompt;
	int		arrlen_pwd;
	int		arrlen_home;

	temp1 = get_name(logname, hostname);
	arrlen_pwd = arr_len(pwd);
	arrlen_home = arr_len(home);
	temp2 = NULL;
	printf("arrlen pwd %d arrlen home %d", arrlen_pwd, arrlen_home);
	if (arrlen_pwd - arrlen_home > 0 && arrlen_pwd > 0)
		temp2 = get_wd(pwd, arrlen_pwd - arrlen_home);
	else if (arrlen_pwd - arrlen_home < 0 && arrlen_pwd > 0)
		temp2 = get_wd(home, arrlen_home);
	else if (arrlen_pwd == 0 || arrlen_pwd - arrlen_home == 0)
		temp2 = ft_strdup("$");
	prompt = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (prompt);
}

char	*init_prompt(void)
{
	char	*logname;
	char	**pwd;
	char	*prompt;
	char	**hostname;
	char	**home;

	prompt = NULL;
	logname = getenv("LOGNAME");
	pwd = ft_split(getenv("PWD"), '/');
	home = ft_split(getenv("HOME"), '/');
	hostname = ft_split(HSTNM, '.');
	prompt = build_prompt(logname, hostname[0], pwd, home);
	free_arr(hostname);
	free_arr(pwd);
	return (prompt);
}
