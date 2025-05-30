/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolkau <gvardovski@icloud.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:17:17 by svolkau           #+#    #+#             */
/*   Updated: 2025/05/26 18:00:01 by svolkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void readprintdir(char *str)
{
    DIR *dir;
    struct dirent *dirs;
	
    dir = opendir(str);
    if(dir != NULL)
    {
        while((dirs = readdir(dir)) != NULL)
        {
            if ((ft_strncmp(".", dirs->d_name, ft_strlen(dirs->d_name)) != 0) 
			&& (ft_strncmp("..", dirs->d_name, ft_strlen(dirs->d_name)) != 0))
            	ft_printf("%s ", dirs->d_name);
        }
    }
    else
        ft_printf("minishell: echo: Cannot open directory '%s'\n", str);
    closedir(dir);
}

char *cwd()
{
	char buf[1024];
	char *p;
	
    p = getcwd(buf, 1024);
	if (!p)
	{
		perror("minishell: pwd");
		return (NULL);
	}
	return(ft_strdup(p));
}

void print_arr(char **gv, int start, int mes)
{
	int i;
	char *str;

	i = start;
	while(gv[i])
	{
		if ((ft_strncmp("*", gv[i], ft_strlen(gv[i])) == 0))
		{
			str = cwd();
			readprintdir(str);
			free(str);
			if (i < (arr_len(gv)- 1))
				i++;
		}
		if ((ft_strncmp("*", gv[i], ft_strlen(gv[i])) != 0))
			printf("%s", gv[i]);
		if (i != (arr_len(gv) - 1))
			ft_printf("");
		i++;
	}
	if (mes == 0)
		ft_printf("\n");
}

int ft_echo(t_main_dat *main_data, char **gv)
{
	t_main_dat temp;

	temp = *main_data;
	(void)temp;
	if (ft_strlen(gv[0]) > 4)
	{
		ft_printf("minishell: '%s': command not found\n", gv[0]);
		return(1);	
	}
    if (arr_len(gv) == 1)
	{
		ft_printf("\n");
		return(0);
	}
   	if ((ft_strncmp("-n", gv[1], ft_strlen(gv[1])) == 0) && (arr_len(gv) == 2))
	   	ft_printf("");
	if ((ft_strncmp("-n",gv[1], ft_strlen(gv[1])) == 0) && (arr_len(gv) > 2))
	   	print_arr(gv, 2, 1);
	if (ft_strncmp("-n",gv[1], ft_strlen(gv[1])) != 0)
		print_arr(gv, 1, 0);
	return(0);
}
