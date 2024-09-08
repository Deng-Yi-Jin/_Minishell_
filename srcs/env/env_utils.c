/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:18:41 by sinlee            #+#    #+#             */
/*   Updated: 2024/09/07 18:38:45 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	flip_bool_env_vars(char *key)
{
	bool	tmp;

	tmp = !ft_atoi(find_env_vars(key)->value);
	modify_env_vars(key, ft_itoa(tmp));
	return (true);
}

int	find_env(char *key, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)ft_malloc(ft_strlen(key) + 2);
	snprintf(tmp, ft_strlen(key) + 2, "%s=", key);
	while (ft_strncmp(envp[i], tmp, ft_strlen(tmp)) && envp[i] != NULL)
		i++;
	free(tmp);
	if (envp[i] == NULL)
	{
		perror_color("Your environment variables does not exist.");
		return (-1);
	}
	else
		return (i);
}

t_env_var	**dup_darr(char **arr)
{
	t_env_var	**out;
	int			i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	out = ft_malloc((i + 1) * sizeof(t_env_var *));
	out[i] = ft_malloc(sizeof(t_env_var));
	out[i]->key = NULL;
	out[i]->value = NULL;
	while (--i >= 0)
	{
		out[i] = ft_malloc(sizeof(t_env_var));
		out[i]->key = ft_substr(arr[i], 0, ft_strchr(arr[i], '=') - arr[i]);
		out[i]->value = ft_substr(arr[i], ft_strchr(arr[i], '=') - arr[i] + 1,
				ft_strlen(arr[i]));
	}
	return (out);
}

void	free_darr(t_env_var **arr)
{
	int	i;

	i = -1;
	while (arr[++i]->key != NULL)
		free(arr[i]);
	free(arr[i]);
	free(arr);
}
