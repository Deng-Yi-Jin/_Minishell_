/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:18:41 by sinlee            #+#    #+#             */
/*   Updated: 2023/08/20 11:44:28 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool  flip_bool_env_vars(char *key)
{
    bool tmp;

    tmp = !ft_atoi(find_env_vars(key)->value);
    modify_env_vars(key, ft_itoa(tmp));
    return (true);
}

// find env var in original envp
int find_env(char *key, char **envp)
{
    int i;
    char *tmp;

    i = 0;
    tmp = (char *)ft_malloc(ft_strlen(key) + 2);
    snprintf(tmp, ft_strlen(key) + 2, "%s=", key);
    while (ft_strncmp(envp[i], tmp, ft_strlen(tmp)) && envp[i] != NULL)
        i++;
    free(tmp);
    if (envp[i] == NULL)
    {
        perror_color("Dei. Your environment variables does not exist. Nearest IQ Checkup is 5km away tho.");
        return (-1);
    }
    else
        return (i);
}

env_var_t	**dup_darr(char **arr)
{
    env_var_t	**out;
    int		i;

    i = 0;
    while (arr[i] != NULL)
        i++;
    out = ft_malloc((i + 1) * sizeof(env_var_t *));
    out[i] = ft_malloc(sizeof(env_var_t));
    out[i]->key = NULL;
    out[i]->value = NULL;
    while (--i >= 0)
    {
        out[i] = ft_malloc(sizeof(env_var_t));
        out[i]->key = ft_substr(arr[i], 0, ft_strchr(arr[i], '=') - arr[i]);
        out[i]->value = ft_substr(arr[i], ft_strchr(arr[i], '=') - arr[i] + 1, ft_strlen(arr[i]));
    }
    return (out);
}

void	free_darr(env_var_t **arr)
{
	int	i;

	i = -1;
	while (arr[++i]->key != NULL)
		free(arr[i]);
    free(arr[i]);
	free(arr);
}