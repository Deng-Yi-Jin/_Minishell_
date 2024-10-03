/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:08:30 by kytan             #+#    #+#             */
/*   Updated: 2024/10/02 15:53:20 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_new_env_var(t_env_var **new_env_vars, int num_env_vars,
			char *key, char *value)
{
	new_env_vars[num_env_vars] = malloc(sizeof(t_env_var));
	new_env_vars[num_env_vars]->key = key;
	new_env_vars[num_env_vars]->value = value;
}

void	init_null_env_var(t_env_var **new_env_vars, int num_env_vars,
			char *key, char *value)
{
	new_env_vars[num_env_vars + 1] = ft_calloc(1, sizeof(t_env_var));
}

size_t	new_vars_ct(char *unset_key)
{
	size_t	env_ct;
	int		i;

	i = -1;
	env_ct = 0;
	while (g_main->env_vars[++i]->key != NULL)
	{
		if (!ft_strcmp(g_main->env_vars[i]->key, unset_key))
			continue ;
		env_ct++;
	}
	if (g_main->env_vars[i])
		env_ct++;
	return (env_ct);
}

void	add_env_vars(char *key, char *value)
{
	int			i;
	t_env_var	**new_env_vars;
	int			num_env_vars;

	if (key == NULL)
		perror_color("Environment Variables Name CANNOT be NULL!");
	num_env_vars = 0;
	while (g_main->env_vars[num_env_vars]->key != NULL)
		num_env_vars++;
	new_env_vars = (t_env_var **)ft_malloc((num_env_vars + 2)
			* sizeof(t_env_var *));
	i = -1;
	while (++i < num_env_vars)
	{
		new_env_vars[i] = malloc(sizeof(t_env_var));
		new_env_vars[i]->key = g_main->env_vars[i]->key;
		new_env_vars[i]->value = g_main->env_vars[i]->value;
	}
	init_new_env_var(new_env_vars, num_env_vars, key, value);
	init_null_env_var(new_env_vars, num_env_vars, key, value);
	free_darr(g_main->env_vars);
	g_main->env_vars = new_env_vars;
}
