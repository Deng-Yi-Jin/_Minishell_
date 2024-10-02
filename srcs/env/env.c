/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:05:43 by kytan             #+#    #+#             */
/*   Updated: 2024/10/02 15:53:09 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_env_vars(char *key, char *value)
{
	t_env_var	*unset;

	unset = find_env_vars(key);
	if (unset != NULL)
	{
		free(unset->value);
		unset->value = value;
	}
	else
		perror_color("Your environment variables does not exist.");
}

t_env_var	*find_env_vars(char *key)
{
	int	i;

	i = 0;
	if (!key)
		;
	while (g_main->env_vars[i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, key))
			break ;
		i++;
	}
	if (g_main->env_vars[i]->key == NULL)
		return (NULL);
	else
		return (g_main->env_vars[i]);
}

void	free_env_vars(void)
{
	int	i;

	i = -1;
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (g_main->env_vars[i]->key != NULL)
			free(g_main->env_vars[i]->key);
		if (g_main->env_vars[i]->value != NULL)
			free(g_main->env_vars[i]->value);
	}
}

static void	create_new_env_array(t_env_var **new, char *key)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, key))
		{
			free(g_main->env_vars[i]->key);
			free(g_main->env_vars[i]->value);
			continue ;
		}
		init_new_env_var(new, j++, g_main->env_vars[i]->key,
			g_main->env_vars[i]->value);
	}
	new[j] = ft_calloc(1, sizeof(t_env_var));
}

void	delete_env_vars(char *key)
{
	t_env_var	*unset;
	t_env_var	**new;

	unset = find_env_vars(key);
	if (unset == NULL)
		return ;
	new = ft_malloc(new_vars_ct(unset->key) * sizeof(t_env_var *));
	create_new_env_array(new, key);
	free_darr(g_main->env_vars);
	g_main->env_vars = new;
	update_g_envp();
}
