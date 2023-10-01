/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinlee <sinlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:41:03 by sinlee            #+#    #+#             */
/*   Updated: 2023/08/20 12:03:14 by sinlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void add_env_vars(char *key, char *value)
{
    int    i;
    env_var_t **new_env_vars;
    int     num_env_vars;

    if (key == NULL)
        perror_color("Environment Variables Name CANNOT be NULL!");
    num_env_vars = 0;
    while (g_main->env_vars[num_env_vars]->key != NULL)
        num_env_vars++;
    new_env_vars = (env_var_t **)ft_malloc((num_env_vars + 2) * sizeof(env_var_t *));
    i = -1;
    while (++i < num_env_vars)
    {
        new_env_vars[i] = malloc(sizeof(env_var_t));
        new_env_vars[i]->key = g_main->env_vars[i]->key;
        new_env_vars[i]->value = g_main->env_vars[i]->value;
    }
    new_env_vars[num_env_vars] = malloc(sizeof(env_var_t));
    new_env_vars[num_env_vars]->key = key;
    new_env_vars[num_env_vars]->value = value;
    new_env_vars[num_env_vars+1] = malloc(sizeof(env_var_t));
    new_env_vars[num_env_vars+1]->key = NULL;
    new_env_vars[num_env_vars+1]->value = NULL;
    free_darr(g_main->env_vars);
    g_main->env_vars = new_env_vars;
}

void modify_env_vars(char *key, char *value)
{
    env_var_t *tmp;

    tmp = find_env_vars(key);
    if (tmp != NULL)
    {
        free(tmp->value);
        tmp->value = value;
    }
    else
        perror_color("Dei. Your environment variables does not exist. Nearest IQ Checkup is 5km away tho."); // might add in find_env_vars instead
}

env_var_t *find_env_vars(char *key)
{
    int i;

    i = 0;
    while (g_main->env_vars[i]->key != NULL)
    {
        if (!ft_strcmp(g_main->env_vars[i]->key, key))
            break;
        i++;
    }
    if (g_main->env_vars[i]->key == NULL)
        return (NULL);
    else
        return (g_main->env_vars[i]);
}

void free_env_vars(void)
{
    int i;

    i = -1;
    while (g_main->env_vars[++i]->key != NULL)
    {
        if (g_main->env_vars[i]->key != NULL)
            free(g_main->env_vars[i]->key);
        if (g_main->env_vars[i]->value != NULL)
            free(g_main->env_vars[i]->value);
    }
}