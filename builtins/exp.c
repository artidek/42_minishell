/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:29:32 by svolkau           #+#    #+#             */
/*   Updated: 2025/05/24 20:23:33 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printexport(t_shenv *en)
{
	int i;
	char *b;
	t_shenv *head;

	b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	i = 0;
	while(b[i])
	{
		head = en;
		while(head)
    	{
			if (head->key[0] == b[i])
        		ft_printf("declare -x %s=\"%s\"\n", head->key, head->value);
        	head = head->next;
    	}
		i++;
	}
}

int findkey(t_shenv *en, char *key)
{
	while (en)
	{
		if ((ft_strncmp(en->key, key, ft_strlen(key)) == 0)
		&& (ft_strlen(en->key) == ft_strlen(key)))
			return(0);
		en = en->next;
	}
	return(1);
}

int checkcharackters(char *str)
{
	int i;
	size_t n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
		{
			if ((str[i] >= 48) && (str[i] <= 57))
				n += 1;
			if ((str[i] != '=') && (str[i] != '_') && (str[i] <= 48) && (str[i] >= 57))
				return(1);
		}
		i++;
	}
	if (n == ft_strlen(str))
		return(1);
	return(0);
}

int ft_export(t_main_dat *main_data, char **gv)
{
	int i;
	int pos;
	t_shenv *en;
	//char *key;
    //char *value;
	en = main_data->env_cp;
	if ((arr_len(gv) == 1) && (ft_strncmp(gv[0], "export", ft_strlen(gv[0])) != 0))
	{
		printf("‘%s’: command not found\n", gv[0]);
		return (1);
	}
	if ((arr_len(gv) == 1) && (ft_strncmp(gv[0], "export", ft_strlen(gv[0])) == 0))
	{
		printexport(en);
		return (0);
	}
	i = 0;
    while(gv[i])
    {
		pos = getposeql(gv[i]);
		if ((checkcharackters(gv[i]) == 1) || pos == 0)
		{
			printf("minishell: export: ‘%s’: not a valid identifier\n", gv[i]);
			return(1);
		}
      /*   key = ft_substr(gv[i], 0, pos);
		if (findkey == 1)
		{
			free()
		}
        value = ft_substr(gv[i], pos + 1, ft_strlen(gv[i]) - pos - 1);
        addback(&en, new(key, value)); */
        i++;
    }
	return(0);
}

// int main(int gc, char **gv, char **env)
// {
//     (void)gc;
//     (void)gv;
// 	char *gv1[2];
//     t_shenv *en = NULL;

// 	gv1[0] = "env";
// 	gv1[1] = NULL;
//     en = initshellenv(en, env);
// 	char *gv2[3];
// 	gv2[0] = "export";
// 	gv2[1] = "11";
// 	gv2[2] = NULL;
// 	ft_export(en, gv2);
// }
