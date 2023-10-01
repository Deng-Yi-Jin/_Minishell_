/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:05:56 by sinlee            #+#    #+#             */
/*   Updated: 2023/08/19 22:51:47 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env_vars(char *key, char *value)
{
    char *var;
    char **new_envp;
    int num_env_vars;
    int i;

    // +1 for '=' and +1 for NULL terminator
    if (key == NULL)
        perror_color("Environment Variables Name CANNOT be NULL!");
    var = (char *)ft_malloc(ft_strlen(key) + ft_strlen(value) + 2);
    ft_snprintf(var, ft_strlen(key) + ft_strlen(value) + 2, "%s=%s", key, value);
    num_env_vars = 0;
    while (g_main->envp[num_env_vars] != NULL)
        num_env_vars++;
    new_envp = (char **)ft_malloc((num_env_vars + 2) * sizeof(char *));
    i = -1;
    while (++i < num_env_vars)
        new_envp[i] = ft_strdup((g_main->envp)[i]);
    new_envp[num_env_vars] = var;
    new_envp[num_env_vars + 1] = NULL;
    free_jutsu(true, key, value);
    g_main->envp = new_envp;
}

char **find_env_vars(char *key)
{
    int i;
    char *tmp;

    i = 0;
    tmp = (char *)ft_malloc(ft_strlen(key) + 2);
    snprintf(tmp, ft_strlen(key) + 2, "%s=", key);
    while (ft_strncmp((g_main->envp)[i], tmp, ft_strlen(tmp)) && ((g_main->envp)[i] != NULL))
        i++;
    free(tmp);
    if ((g_main->envp)[i] == NULL)
    {
        perror_color("Dei. Your environment variables does not exist. Nearest IQ Checkup is 5km away tho.");
        return (NULL);
    }
    else
        return &(g_main->envp[i]);
}

void modify_env_vars(char *key, char *value)
{
    char *tmp;
    char **var;
    int len;

    var = find_env_vars(key);
    len = ft_strlen(key) + ft_strlen(value) + 2;
    if (tmp != NULL)
    {
        free(*var);
        *var = (char *)ft_malloc(len);
        ft_snprintf(*var, len, "%s=%s", key, value);
    }
    free(value);
}

char *ft_getenv(char *key)
{
    char **var;

    var = find_env_vars(key);
    if (var != NULL)
        return (*var+ ft_strlen(key) + 1);
    else
        return (NULL);
}